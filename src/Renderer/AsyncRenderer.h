//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_ASYNCRENDERER_H
#define LII_ASYNCRENDERER_H
#include "AsyncRenderingProvider.h"
#include "blockingconcurrentqueue.h"
#include "RenderMessage.h"
#include "RenderingModel.h"

class AsyncRenderer : public AsyncRenderingProvider
{
private:
    moodycamel::BlockingConcurrentQueue<std::unique_ptr<RenderMessage>> messageQueue;
    bool render = false;
    void PerformRenderCommand(std::unique_ptr<RenderMessage> message);
    std::vector<std::unique_ptr<RenderingModel>> renderingModels;
    std::vector<std::unique_ptr<RendererProxy>> proxies;
public:
    std::future<EllipseProxy *> RequestEllipseProxy() override;
    std::future<ModelProxy *> RequestModelProxy() override;
    std::future<LineProxy *> RequestLineProxy() override;
    std::future<TextProxy *> RequestTextProxy() override;
    std::future<RectangleProxy *> RequestRectangleProxy() override;
    void RequestEllipseProxy(std::function<void(RendererProxy &)> onCreatedAction) override;
    void RequestModelProxy(std::function<void(RendererProxy &)> onCreatedAction) override;
    void RequestLineProxy(std::function<void(RendererProxy &)> onCreatedAction) override;
    void RequestTextProxy(std::function<void(RendererProxy &)> onCreatedAction) override;
    void RequestRectangleProxy(std::function<void(RendererProxy &)> function) override;
    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    void Render() override;

    void OnInit(Core &coreWindow) override;

    void OnDestroy(Core &coreWindow) override;

    void OnRemove(Core &coreWindow) override;

    void WaitForSyncToFinish() override;

};


#endif //LII_ASYNCRENDERER_H
