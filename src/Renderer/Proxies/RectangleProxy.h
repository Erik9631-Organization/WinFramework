//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RECTANGLEPROXY_H
#define LII_RECTANGLEPROXY_H
#include "Movable.h"
#include "Resizable.h"
#include <vector>
#include "RenderProxy.h"
#include <unordered_map>
#include "Commands.h"
#include "DefaultViewport.h"
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "RenderingProxyMessageSender.h"
#include <concurrentqueue.h>

class RenderingConsumer;
class RectangleModel;
class RenderMessage;

class RectangleProxy : public Movable, public Resizable, public RenderProxy, public MoveSubscriber, public ResizeSubscriber
{
private:
    static constexpr glm::vec3 defaultVec4 = glm::vec4{0, 0, 0, 0};
    static constexpr glm::ivec4 defaultColorVec = glm::vec4{0, 0, 0, 0};
    RectangleModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    std::vector<ResizeSubscriber*>resizeSubscribers;
    RenderingProxyMessageSender messageSender;
    std::vector<Viewport2Subscriber*> viewPortSubscribers;
    void SendRenderingMessage(std::unique_ptr<RenderMessage> message);
public:

    void SetThickness(float thickness);

    void SetFill(bool fill);

    const glm::ivec4& GetColor();

    void SetColor(const glm::ivec4 &color);

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    [[nodiscard]] const glm::vec3 & GetSize() const override;

    void SetSize(const glm::vec3 &size, bool emit = true) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    const size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    [[nodiscard]] bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_RECTANGLEPROXY_H
