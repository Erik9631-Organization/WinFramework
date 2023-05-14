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
    void CreateModelFromMessage(std::unique_ptr<RenderMessage> message);
    void RenderLoop();

public:
    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;
    void SwapScreenBuffer() override;

    void SetViewPortSize(const glm::ivec2 &size) override;

    void RequestModel(RenderProxy &proxy) override;

    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

};


#endif //LII_DEFAULTASYNCRENDERCOMMANDHANDLER_H
