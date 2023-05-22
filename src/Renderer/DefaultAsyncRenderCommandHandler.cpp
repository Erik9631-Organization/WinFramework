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
#include <tracy/Tracy.hpp>
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
            FrameMark;
            invalidated = false;
            renderer->Render();
            renderer->SwapScreenBuffer();
            break;
        }
        case Commands::SetViewport:
        {
            auto size = message->GetData<glm::ivec2>();
            renderer->SetViewportSize(size);
            RedrawScene();
            break;
        }
        case Commands::Init:
        {
            renderer->OnCoreInit(message->GetData<EventCoreLifecycleInfo>());
            break;
        }
        case Commands::Start:
        {
            renderer->OnCoreStart(message->GetData<EventCoreLifecycleInfo>());
            break;
        }
        case Commands::Stop:
        {
            render = false;
            renderer->OnCoreStop(message->GetData<EventCoreLifecycleInfo>());
            break;
        }
        case Commands::Destroy:
        {
            renderer->OnCoreDestroy(message->GetData<EventCoreLifecycleInfo>());
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
    auto message = RenderMessage::Create(Commands::SetViewport, size);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::RequestModel(RenderProxy &proxy)
{
    auto message = RenderMessage::CreateModelRequestMessage(proxy.GetModelRequestCommand(), &proxy);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnCoreInit(const EventCoreLifecycleInfo &e)
{
    renderer = LiiInjector::Injector::GetInstance().ResolveTransient<Renderer>();
    auto message = RenderMessage::Create(Commands::Init, e);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    render = true;
    renderThread = &LiiApplication::GetInstance()->CreateThread([&]{RenderLoop();}, "RenderThread");
    if(redrawLoop == true)
        redrawThread = &LiiApplication::GetInstance()->CreateThread([&]{RedrawLoop();}, "RedrawThread");
    auto message = RenderMessage::Create(Commands::Start, e);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnCoreStop(const EventCoreLifecycleInfo &e)
{
    auto message = RenderMessage::Create(Commands::Stop, e);
    redrawLoop = false;
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{
    auto message = RenderMessage::Create(Commands::Destroy, e);
    this->ReceiveCommand(std::move(message));
}

void DefaultAsyncRenderCommandHandler::RedrawLoop()
{
    int N = 1; // Set N milliseconds
    while(redrawLoop)
    {
        RedrawScene();
    }
}

