//
// Created by erik9 on 12/19/2022.
//

#include "DefaultAsyncRenderCommandHandler.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "LineModel.h"
#include "RenderMessage.h"
#include "MessageGenerateModel.h"
#include <algorithm>
#include <execution>
#include <iostream>
#include "LiiApplication.h"
#include <Injector.hpp>

//TODO add release model so model can be also removed

void DefaultAsyncRenderCommandHandler::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    messageQueue.enqueue(std::move(message));
}

void DefaultAsyncRenderCommandHandler::CreateModelFromMessage(std::unique_ptr<RenderMessage> message)
{
    auto proxy = message->GetData<RenderProxy*>();
    auto modelPtr = renderer->CreateModel(message->GetSubMessageId());
    proxy->OnModelCreated(modelPtr, this);
    RedrawScene();
}

void DefaultAsyncRenderCommandHandler::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetMessageId())
    {
        case Commands::RequestModel:
        {
            CreateModelFromMessage(std::move(message));
            break;
        }
        case Commands::Property:
        {
            const auto id = message->GetReceiverId();
            auto sender = message->GetRenderMessageSender();
            auto messageSubId = message->GetSubMessageId();
            auto model = renderer->GetModel(id);
            if(model != nullptr)
                renderer->GetModel(id)->ReceiveCommand(std::move(message));
            else
                std::cout << "Model is null exception" << std::endl;
            RedrawScene();
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

void DefaultAsyncRenderCommandHandler::SetViewPortSize(const glm::ivec2 &size)
{
    renderer->SetViewportSize(size);
}

void DefaultAsyncRenderCommandHandler::RequestModel(RenderProxy &proxy)
{
    auto message = RenderMessage::CreateModelRequestMessage(proxy.GetModelRequestCommand(), &proxy);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnCoreInit(const EventCoreLifecycleInfo &e)
{
    render = true;
    renderer = LiiInjector::Injector::GetInstance().ResolveTransient<Renderer>();
    renderer->OnCoreInit(e);
    renderThread = &LiiApplication::GetInstance()->CreateThread([&]{RenderLoop();}, "RenderThread");
}

void DefaultAsyncRenderCommandHandler::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    renderer->OnCoreStart(e);
}

void DefaultAsyncRenderCommandHandler::OnCoreStop(const EventCoreLifecycleInfo &e)
{
    renderer->OnCoreStop(e);
    auto quitMessage = RenderMessage::Create(Commands::Quit, nullptr);
    this->ReceiveCommand(std::move(quitMessage));
}

void DefaultAsyncRenderCommandHandler::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{
    renderer->OnCoreDestroy(e);
}
