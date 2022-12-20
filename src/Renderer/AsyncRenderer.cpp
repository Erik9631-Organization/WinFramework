//
// Created by erik9 on 12/19/2022.
//

#include "AsyncRenderer.h"
#include "MessageIds.h"
#include "RectangleModel.h"
#include "RenderingProviderManager.h"
#include <future>
#include "RenderMessage.h"

std::future<EllipseProxy *> AsyncRenderer::RequestEllipseProxy()
{
    return std::future<EllipseProxy *>();
}

std::future<ModelProxy *> AsyncRenderer::RequestModelProxy()
{
    return std::future<ModelProxy *>();
}

std::future<LineProxy *> AsyncRenderer::RequestLineProxy()
{
    return std::future<LineProxy *>();
}

std::future<TextProxy *> AsyncRenderer::RequestTextProxy()
{
    return std::future<TextProxy *>();
}

std::future<RectangleProxy *> AsyncRenderer::RequestRectangleProxy()
{
    auto rectangleProxyPromise = new std::promise<RectangleProxy*>();
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(CommandIds::RequestRectangle, rectangleProxyPromise);
    this->ReceiveCommand(std::move(message));
    return rectangleProxyPromise->get_future();
}

void AsyncRenderer::RequestEllipseProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}

void AsyncRenderer::RequestModelProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}

void AsyncRenderer::RequestLineProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}

void AsyncRenderer::RequestTextProxy(std::function<void(RendererProxy &)> onCreatedAction)
{

}

void AsyncRenderer::RequestRectangleProxy(std::function<void(RendererProxy &)> function)
{

}

void AsyncRenderer::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    messageQueue.enqueue(std::move(message));
}

void AsyncRenderer::Render()
{
    std::vector<std::future<void>> renderWorkers;
    while(render)
    {
        std::unique_ptr<RenderMessage> message;
        messageQueue.wait_dequeue(message);
        //std::future<void> futureResult = std::async(std::launch::async, [&]{ PerformRenderCommand(std::move(message));});
        PerformRenderCommand(std::move(message));
//        renderWorkers.push_back(std::move(futureResult));
    }

//    for(auto& workers : renderWorkers)
//        workers.wait()

}

void AsyncRenderer::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetId())
    {
        case CommandIds::RequestRectangle:
            auto rectangleModel = std::make_unique<RectangleModel>();
            auto promise = message->GetData<std::promise<RectangleProxy*>*>();
            //rectangleModel->SetRenderer() We need a manager that contains the renderer
            renderingModels.push_back(std::move(rectangleModel));
            break;

    }
}


void AsyncRenderer::OnInit(Core &coreWindow)
{
    render = true;
}

void AsyncRenderer::OnDestroy(Core &coreWindow)
{

}

void AsyncRenderer::OnRemove(Core &coreWindow)
{

}

void AsyncRenderer::WaitForSyncToFinish()
{

}

