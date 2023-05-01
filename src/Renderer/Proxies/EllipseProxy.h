//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_ELLIPSEPROXY_H
#define LII_ELLIPSEPROXY_H
#include "RenderProxy.h"
#include "Movable.h"
#include "vec2.hpp"
#include "RenderingModel.h"
#include "Resizable.h"
#include "RenderingProxyMessageSender.h"
class EllipseModel;

class EllipseProxy : public virtual Movable, public Resizable, public virtual RenderProxy
{
private:
    static constexpr glm::vec3 defaultVector = glm::vec4{0};
    static constexpr glm::ivec4 defaultColorVec = glm::vec4{0};
    RenderingModel *renderingModel = nullptr;
    RenderingProxyMessageSender messageSender;
    EllipseModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    std::vector<ResizeSubscriber*>resizeSubscribers;
    std::vector<Viewport2Subscriber*>viewPortSubscribers;
public:
    void SetFill(bool fill);

    bool GetFill();

    void SetColor(const glm::ivec4 &color);

    const glm::ivec4 & GetColor();

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    const size_t & GetAssociatedModelId() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    ~EllipseProxy() override = default;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    [[nodiscard]] const glm::vec3 & GetSize() const override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

    void SetViewportSize(const glm::vec3 &viewPort) override;

    void SetViewportPosition(const glm::vec3 &position) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    [[nodiscard]] bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

    void SetSize(const glm::vec3 &size, bool emit = true) override;

};


#endif //LII_ELLIPSEPROXY_H
