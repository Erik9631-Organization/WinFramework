//
// Created by erik9 on 12/19/2022.
//

#include "AsyncRenderer.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "LineModel.h"
#include "RenderingProviderManager.h"
#include <future>
#include "RenderMessage.h"

std::future<std::unique_ptr<EllipseProxy>> AsyncRenderer::RequestEllipseProxy()
{
    return std::future<std::unique_ptr<EllipseProxy>>();
}

std::future<std::unique_ptr<ModelProxy>> AsyncRenderer::RequestModelProxy()
{
    return std::future<std::unique_ptr<ModelProxy>>();
}

std::future<std::unique_ptr<LineProxy>> AsyncRenderer::RequestLineProxy()
{
    auto lineProxyPromise = new std::promise<std::unique_ptr<LineProxy>>();
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestLine, lineProxyPromise);
    this->ReceiveCommand(std::move(message));
    return lineProxyPromise->get_future();
}

std::future<std::unique_ptr<TextProxy>> AsyncRenderer::RequestTextProxy()
{
    return std::future<std::unique_ptr<TextProxy>>();
}

std::future<std::unique_ptr<RectangleProxy>> AsyncRenderer::RequestRectangleProxy()
{
    auto rectangleProxyPromise = new std::promise<std::unique_ptr<RectangleProxy>>();
    //TODO FIND A SAFE WAY
    // !!!!WARNING THIS IS DANGEROUS, CAN CAUSE MEMORY LEAK!!!!
    auto message = RenderMessage::Create(Commands::RequestRectangle, rectangleProxyPromise);
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
        PerformRenderCommand(std::move(message));
    }

}

void AsyncRenderer::PerformRenderCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetId())
    {
        case Commands::RequestRectangle:
        {
            auto rectangleModel = std::make_unique<RectangleModel>();
            auto rectanglePromise = message->GetData<std::promise<std::unique_ptr<RectangleProxy>>*>();
            auto rectangleProxy = std::make_unique<RectangleProxy>();
            //rectangleModel->SetRenderer() We need a manager that contains the renderer
            rectanglePromise->set_value(std::move(rectangleProxy));
            renderingModels.push_back(std::move(rectangleModel));
            break;
        }

        case Commands::RequestLine:
        {
            auto lineModel = std::make_unique<LineModel>();
            auto linePromise = message->GetData<std::promise<std::unique_ptr<LineProxy>>*>();
            auto proxy = std::make_unique<LineProxy>();
            linePromise->set_value(std::move(proxy));
            //rectangleModel->SetRenderer() We need a manager that contains the renderer
            renderingModels.push_back(std::move(lineModel));
        }
        break;


    }
}


void AsyncRenderer::OnInit(Core &coreWindow)
{
    render = true;
    renderThread = std::make_unique<std::thread>([&]{Render();});
}

void AsyncRenderer::OnDestroy(Core &coreWindow)
{
    renderThread->join();
}

void AsyncRenderer::OnRemove(Core &coreWindow)
{

}

void AsyncRenderer::WaitForSyncToFinish()
{

}

