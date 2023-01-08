//
// Created by erik9 on 12/19/2022.
//

#include "DefaultRenderCommandHandler.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "LineModel.h"
#include "RenderingProviderManager.h"
#include "RenderMessage.h"
#include "CreateModelMessage.h"
#include <algorithm>
#include <execution>

std::future<std::unique_ptr<EllipseProxy>> DefaultRenderCommandHandler::RequestEllipseProxy()
{
    return std::future<std::unique_ptr<EllipseProxy>>();
}

std::future<std::unique_ptr<ModelProxy>> DefaultRenderCommandHandler::RequestModelProxy()
{
    return std::future<std::unique_ptr<ModelProxy>>();
}

std::future<std::unique_ptr<LineProxy>> DefaultRenderCommandHandler::RequestLineProxy()
{
    auto linePromise = std::promise<std::unique_ptr<LineProxy>>();
    auto createMessage = new CreateModelMessage(std::move(linePromise));
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, createMessage);
    this->ReceiveCommand(std::move(message));
    return createMessage->GetRendererProxyPromise().get_future();
}

void DefaultRenderCommandHandler::RequestLineProxy(std::function<void(std::unique_ptr<LineProxy>)> onCreatedAction)
{
    auto createMessage = new CreateModelMessage(onCreatedAction);
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, createMessage);
    this->ReceiveCommand(std::move(message));
}


std::future<std::unique_ptr<TextProxy>> DefaultRenderCommandHandler::RequestTextProxy()
{
    return std::future<std::unique_ptr<TextProxy>>();
}

std::future<std::unique_ptr<RectangleProxy>> DefaultRenderCommandHandler::RequestRectangleProxy()
{
    auto rectanglePromise = std::promise<std::unique_ptr<RectangleProxy>>();
    auto createMessage = new CreateModelMessage(std::move(rectanglePromise));
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, createMessage);
    this->ReceiveCommand(std::move(message));
    return createMessage->GetRendererProxyPromise().get_future();
}

void DefaultRenderCommandHandler::RequestRectangleProxy(std::function<void(std::unique_ptr<RectangleProxy>)> function)
{
    auto createMessage = new CreateModelMessage(function);
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, createMessage);
    this->ReceiveCommand(std::move(message));
}


void DefaultRenderCommandHandler::RequestEllipseProxy(std::function<void(RenderProxy &)> onCreatedAction)
{

}

void DefaultRenderCommandHandler::RequestModelProxy(std::function<void(RenderProxy &)> onCreatedAction)
{

}

void DefaultRenderCommandHandler::RequestTextProxy(std::function<void(RenderProxy &)> onCreatedAction)
{

}

void DefaultRenderCommandHandler::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    messageQueue.enqueue(std::move(message));
}

void DefaultRenderCommandHandler::Render()
{


}
//TODO: Refactor simplify
void DefaultRenderCommandHandler::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetId())
    {
        case Commands::RequestRectangle:
        {
            CreateModelFromMessage<RectangleModel, RectangleProxy>(std::move(message));
            break;
        }
        case Commands::RequestLine:
        {
            CreateModelFromMessage<LineModel, LineProxy>(std::move(message));
            break;
        }
        case Commands::Property:
        {
            const auto id = message->GetReceiverId();
            provider->GetModel(id)->ReceiveCommand(std::move(message));
            break;
        }
    }
}


void DefaultRenderCommandHandler::OnInit(Core &coreWindow)
{
    render = true;
    provider = RenderingProviderManager::GetRenderingProviderManager()->Create();
    provider->OnInit(coreWindow);
    renderThread = std::make_unique<std::thread>([&]{RenderLoop();});
}

void DefaultRenderCommandHandler::OnDestroy(Core &coreWindow)
{
    provider->OnDestroy(coreWindow);
    renderThread->join();
}

void DefaultRenderCommandHandler::OnRemove(Core &coreWindow)
{

}

void DefaultRenderCommandHandler::WaitForSyncToFinish()
{

}

void DefaultRenderCommandHandler::SwapScreenBuffer()
{
    if(provider == nullptr)
        return;
    RedrawScene();

    provider->SwapScreenBuffer();
}

//TODO Clean up this unused interface
std::unique_ptr<Renderer> DefaultRenderCommandHandler::AcquireRenderer()
{
    return nullptr;
}

void DefaultRenderCommandHandler::RenderLoop()
{
    while(render)
    {
        std::unique_ptr<RenderMessage> message;
        messageQueue.wait_dequeue(message);
        PerformRenderCommand(std::move(message));
    }
}
//TODO TODAY Move the Redraw into the Renderer.
//The renderer should keep track of the scene and when it is valid.
void DefaultRenderCommandHandler::RedrawScene()
{
    provider->Render();
}

void DefaultRenderCommandHandler::AddModel(std::unique_ptr<RenderingModel> renderingModel)
{
    provider->AddModel(std::move(renderingModel));
}

RenderingModel *DefaultRenderCommandHandler::GetModel(size_t index)
{
    return provider->GetModel(index);
}

const std::vector<std::unique_ptr<RenderingModel>>& DefaultRenderCommandHandler::GetRenderingModels()
{
    return provider->GetRenderingModels();
}

