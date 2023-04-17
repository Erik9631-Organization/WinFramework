//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_DEFAULTASYNCRENDERCOMMANDHANDLER_H
#define LII_DEFAULTASYNCRENDERCOMMANDHANDLER_H
#include "AsyncRenderCommandHandler.h"
#include "blockingconcurrentqueue.h"
#include "RenderMessage.h"
#include "RenderingModel.h"
#include "RectangleProxy.h"
#include "MessageGenerateModel.h"
#include <future>
#include "TextModel.h"


class DefaultAsyncRenderCommandHandler : public AsyncRenderCommandHandler
{
private:
    moodycamel::BlockingConcurrentQueue<std::unique_ptr<RenderMessage>> messageQueue;
    bool render = false;
    bool invalidated = false;
    void RedrawScene();

    void PerformRenderCommand(std::unique_ptr<RenderMessage> message);
    std::vector<std::unique_ptr<RenderProxy>> proxies;
    std::thread* renderThread;
    std::unique_ptr<Renderer> renderer;
    template<typename ProxyType>
    void CreateModelFromMessage(std::unique_ptr<RenderMessage> message)
    {
        auto createData = message->GetData<MessageGenerateModel<ProxyType*>*>();
        auto proxy = createData->GetRendererProxy();
        auto modelPtr = renderer->CreateModel(message->GetMessageId());
        proxy->OnModelCreated(modelPtr, this);
        delete createData;
        RedrawScene();
    }

    void RenderLoop();

public:
    void RequestEllipseProxy(EllipseProxy &proxy) override;
    std::unique_ptr<RenderProxy> RequestModelProxy() override;
    void RequestLineModel(LineProxy &proxy) override;
    void RequestTextModel(TextProxy &proxy) override;
    void RequestRectangleModel(RectangleProxy &proxy) override;
    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;
    void SwapScreenBuffer() override;

    void OnInit(Core &core) override;

    void OnDestroy(Core &core) override;

    void SetViewportSize(int width, int height) override;

    void SetViewportSize(const glm::ivec2 &size) override;

};


#endif //LII_DEFAULTASYNCRENDERCOMMANDHANDLER_H
