//
// Created by erik9 on 12/19/2022.
//

#include "DefaultAsyncRenderCommandHandler.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "LineModel.h"
#include "RenderingProviderManager.h"
#include "RenderMessage.h"
#include "MessageGenerateModel.h"
#include <algorithm>
#include <execution>
#include <iostream>
#include "ApplicationController.h"

std::unique_ptr<LineProxy> DefaultAsyncRenderCommandHandler::RequestLineProxy()
{
    auto proxy = std::make_unique<LineProxy>();
    auto createMessage = new MessageGenerateModel(proxy.get());
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, createMessage);
    this->ReceiveCommand(std::move(message));
    return proxy;
}

std::unique_ptr<RectangleProxy> DefaultAsyncRenderCommandHandler::RequestRectangleProxy()
{
    auto proxy = std::make_unique<RectangleProxy>();
    auto createMessage = new MessageGenerateModel(proxy.get());
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, createMessage);
    this->ReceiveCommand(std::move(message));
    return proxy;
}

std::unique_ptr<RenderProxy> DefaultAsyncRenderCommandHandler::RequestEllipseProxy()
{
    return nullptr;
}

std::unique_ptr<RenderProxy> DefaultAsyncRenderCommandHandler::RequestModelProxy()
{
    return nullptr;
}

std::unique_ptr<TextProxy> DefaultAsyncRenderCommandHandler::RequestTextProxy()
{
    auto proxy = std::make_unique<TextProxy>();
    auto createMessage = new MessageGenerateModel(proxy.get());
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, createMessage);
    this->ReceiveCommand(std::move(message));
    return proxy;
}

void DefaultAsyncRenderCommandHandler::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    messageQueue.enqueue(std::move(message));
}

void DefaultAsyncRenderCommandHandler::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetMessageId())
    {
        case Commands::RequestRectangle:
        {
            CreateModelFromMessage<RectangleProxy>(std::move(message));
            break;
        }
        case Commands::RequestLine:
        {
            CreateModelFromMessage<LineProxy>(std::move(message));
            break;
        }
        case Commands::Property:
        {
            const auto id = message->GetReceiverId();
            auto sender = message->GetRenderMessageSender();
            auto messageSubId = message->GetSubMessageId();
            renderer->GetModel(id)->ReceiveCommand(std::move(message));

            if(sender!= nullptr)
                sender->OnRenderMessageProcessed(messageSubId);
            break;
        }
        case Commands::Redraw:
        {
            invalidated = false;
            renderer->Render();
            renderer->SwapScreenBuffer();
            break;
        }
        case Commands::Quit:
        {
            render = false;
            break;
        }
        default:
            break;
    }
}

//TODO: MAKE THIS THREAD SAFE SHOULD BE A MESSAGE
void DefaultAsyncRenderCommandHandler::SwapScreenBuffer()
{
    if(renderer == nullptr)
        return;
    RedrawScene();
}

void DefaultAsyncRenderCommandHandler::RenderLoop()
{
    while(render)
    {
        std::unique_ptr<RenderMessage> message;
        messageQueue.wait_dequeue(message);
        PerformRenderCommand(std::move(message));
    }
}

void DefaultAsyncRenderCommandHandler::RedrawScene()
{
    if(invalidated)
        return;
    auto message = RenderMessage::Create(Commands::Redraw, nullptr);
    invalidated = true;
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnInit(Core &core)
{
    render = true;
    renderer = RenderingProviderManager::GetRenderingProviderManager()->Create();
    renderer->OnInit(core);
    renderThread = &ApplicationController::GetApplicationController()->CreateThread([&]{RenderLoop();}, "RenderThread");
}

void DefaultAsyncRenderCommandHandler::OnDestroy(Core &core)
{
    renderer->OnDestroy(core);
    auto quitMessage = RenderMessage::Create(Commands::Quit, nullptr);
    this->ReceiveCommand(std::move(quitMessage));
}

void DefaultAsyncRenderCommandHandler::SetViewportSize(int width, int height)
{
    renderer->SetViewportSize(width, height);
}

void DefaultAsyncRenderCommandHandler::SetViewportSize(const glm::ivec2 &size)
{
    renderer->SetViewportSize(size);
}
