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
    RenderingModel *renderingModel;
    RenderingProxyMessageSender messageSender;
    EllipseModel* model;
    std::vector<MoveSubscriber*>moveSubscribers;
    std::vector<ResizeSubscriber*>resizeSubscribers;
    std::vector<Viewport2Subscriber*>viewPortSubscribers;
public:
    void SetFill(bool fill);

    bool GetFill();

    void SetColor(const glm::ivec4 &color);

    const glm::ivec4 & GetColor();

    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 & GetAbsolutePosition() override;

    void SetPosition(glm::vec4 position, bool emit) override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w, bool emit) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    const size_t & GetAssociatedModelId() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    ~EllipseProxy() override = default;

    float GetZ() override;

    float GetW() override;

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    const glm::vec4 &GetSize() override;

    float GetWidth() override;

    float GetHeight() override;

    void SetSize(const glm::vec4 &size, bool emit) override;

    void SetSize(glm::vec4 size) override;

    void SetSize(float width, float height, bool emit) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width, bool emit) override;

    void SetWidth(float width) override;

    void SetHeight(float height, bool emit) override;

    void SetHeight(float height) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

    void SetViewportSize(const glm::vec4 &viewPort) override;

    void SetViewportPosition(const glm::vec4 &position) override;

    glm::vec4 &GetViewportSize() override;

    glm::vec4 &GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber *subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber *subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

};


#endif //LII_ELLIPSEPROXY_H
