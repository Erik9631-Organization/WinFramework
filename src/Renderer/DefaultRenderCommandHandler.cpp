//
// Created by erik9 on 12/19/2022.
//

#include "DefaultRenderCommandHandler.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "LineModel.h"
#include "RenderingProviderManager.h"
#include <future>
#include "RenderMessage.h"
#include "CreateMessage.h"

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
    auto linePromise = std::make_unique<std::promise<std::unique_ptr<LineProxy>>>();
    auto createMessage = new CreateMessage(std::move(linePromise));
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, createMessage);
    this->ReceiveCommand(std::move(message));
    return createMessage->GetRendererProxyPromise()->get_future();
}

void DefaultRenderCommandHandler::RequestLineProxy(std::function<void(std::unique_ptr<RendererProxy>)> onCreatedAction)
{
    auto lineProxyPromise = new std::promise<std::unique_ptr<LineProxy>>();
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, lineProxyPromise);
    this->ReceiveCommand(std::move(message));
}


std::future<std::unique_ptr<TextProxy>> DefaultRenderCommandHandler::RequestTextProxy()
{
    return std::future<std::unique_ptr<TextProxy>>();
}

std::future<std::unique_ptr<RectangleProxy>> DefaultRenderCommandHandler::RequestRectangleProxy()
{
    auto rectanglePromise = std::make_unique<std::promise<std::unique_ptr<RectangleProxy>>>();
    auto createMessage = new CreateMessage(std::move(rectanglePromise));
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, createMessage);
    this->ReceiveCommand(std::move(message));
    return createMessage->GetRendererProxyPromise()->get_future();
}

void DefaultRenderCommandHandler::RequestRectangleProxy(std::function<void(std::unique_ptr<RendererProxy>)> function)
{

}


void DefaultRenderCommandHandler::RequestEllipseProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}

void DefaultRenderCommandHandler::RequestModelProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}


void DefaultRenderCommandHandler::RequestTextProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}


void DefaultRenderCommandHandler::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    messageQueue.enqueue(std::move(message));
}

void DefaultRenderCommandHandler::Render()
{
    std::vector<std::future<void>> renderWorkers;
    while(render)
    {
        std::unique_ptr<RenderMessage> message;
        messageQueue.wait_dequeue(message);
        PerformRenderCommand(std::move(message));
    }

}
//TODO: Refactor simplify
void DefaultRenderCommandHandler::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetId())
    {
        case Commands::RequestRectangle:
        {
            auto rectangleModel = std::make_unique<RectangleModel>();
            auto createData = message->GetData<CreateMessage<RectangleProxy>*>();
            auto proxy = std::make_unique<RectangleProxy>();
            rectangleModel->SetRenderingProvider(provider.get());
            auto modelPtr = rectangleModel.get();
            renderingModels.push_back(std::move(rectangleModel));
            if(createData->GetRendererProxyPromise() != nullptr)
                createData->GetRendererProxyPromise()->set_value(std::move(proxy));
            else
                createData->GetFutureCallback()->operator()(std::move(proxy));
            modelPtr->Redraw();
            break;
        }

        case Commands::RequestLine:
        {
            auto lineModel = std::make_unique<LineModel>();
            auto createData = message->GetData<CreateMessage<LineProxy>*>();
            auto proxy = std::make_unique<LineProxy>();
            lineModel->SetRenderingProvider(provider.get());
            auto modelPtr = lineModel.get();
            renderingModels.push_back(std::move(lineModel));
            if(createData->GetRendererProxyPromise() != nullptr)
                createData->GetRendererProxyPromise()->set_value(std::move(proxy));
            else
                createData->GetFutureCallback()->operator()(std::move(proxy));

            modelPtr->Redraw();
            break;
        }
        case Commands::Property:
        {
            break;
        }
    }
}


void DefaultRenderCommandHandler::OnInit(Core &coreWindow)
{
    render = true;
    provider = RenderingProviderManager::GetRenderingProviderManager()->GetRenderingProviderManager()->Create();
    renderThread = std::make_unique<std::thread>([&]{Render();});
}

void DefaultRenderCommandHandler::OnDestroy(Core &coreWindow)
{
    renderThread->join();
}

void DefaultRenderCommandHandler::OnRemove(Core &coreWindow)
{

}

void DefaultRenderCommandHandler::WaitForSyncToFinish()
{

}
