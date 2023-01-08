//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_DEFAULTRENDERCOMMANDHANDLER_H
#define LII_DEFAULTRENDERCOMMANDHANDLER_H
#include "AsyncRenderCommandHandler.h"
#include "blockingconcurrentqueue.h"
#include "RenderMessage.h"
#include "RenderingModel.h"
#include "CreateModelMessage.h"
#include <future>
class DefaultRenderCommandHandler : public AsyncRenderCommandHandler
{
private:
    moodycamel::BlockingConcurrentQueue<std::unique_ptr<RenderMessage>> messageQueue;
    bool render = false;
    bool drawAsync = false;
    void RedrawScene();

    void PerformRenderCommand(std::unique_ptr<RenderMessage> message);
    std::vector<std::unique_ptr<RenderProxy>> proxies;
    std::unique_ptr<std::thread> renderThread;
    std::unique_ptr<Renderer> provider;
    template<typename ModelType, typename ProxyType>
    void CreateModelFromMessage(std::unique_ptr<RenderMessage> message)
    {
        auto rectangleModel = std::make_unique<ModelType>();
        auto createData = message->GetData<CreateModelMessage<std::unique_ptr<ProxyType>>*>();
        auto proxy = std::make_unique<ProxyType>();
        proxy->SetRenderingConsumer(this);
        rectangleModel->SetRenderingProvider(provider.get());
        auto modelPtr = rectangleModel.get();
        provider->AddModel(std::move(rectangleModel));
        size_t id = provider->GetRenderingModels().size() - 1;
        modelPtr->SetAssociatedModelId(id);
        proxy->SetAssociatedModel(modelPtr);
        if(createData->IsCallbackSet() == false)
            createData->GetRendererProxyPromise().set_value(std::move(proxy));
        else
            createData->GetFutureCallback().operator()(std::move(proxy));
        delete createData;
    }

    void RenderLoop();

public:
    std::future<std::unique_ptr<EllipseProxy>> RequestEllipseProxy() override;
    std::future<std::unique_ptr<ModelProxy>> RequestModelProxy() override;
    std::future<std::unique_ptr<LineProxy>> RequestLineProxy() override;
    std::future<std::unique_ptr<TextProxy>> RequestTextProxy() override;
    std::future<std::unique_ptr<RectangleProxy>> RequestRectangleProxy() override;
    void RequestEllipseProxy(std::function<void(RenderProxy &)> onCreatedAction) override;
    void RequestModelProxy(std::function<void(RenderProxy &)> onCreatedAction) override;
    void RequestLineProxy(std::function<void(std::unique_ptr<LineProxy>)> onCreatedAction) override;
    void RequestTextProxy(std::function<void(RenderProxy &)> onCreatedAction) override;
    void RequestRectangleProxy(std::function<void(std::unique_ptr<RectangleProxy>)> function) override;
    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;
    void SwapScreenBuffer() override;

    void OnInit(Core &core) override;

    void OnDestroy(Core &core) override;

};


#endif //LII_DEFAULTRENDERCOMMANDHANDLER_H
