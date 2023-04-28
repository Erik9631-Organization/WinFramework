//
// Created by erik9 on 4/18/2023.
//

#ifndef LII_ELLIPSEMODEL_H
#define LII_ELLIPSEMODEL_H


#include "RenderingModel.h"
#include "ModelViewport.h"
#include "Resizable.h"
#include "Movable.h"
#include "MovableModelBehavior.h"
#include "ResizableModelBehavior.h"

class EllipseModel : public RenderingModel, public Resizable, public Movable
{
private:
    size_t id = -1;
    bool fill = false;
    bool visible = true;
    bool renderFromCenter = true;
    ModelViewport viewPort;
    glm::ivec4 color{255, 255, 255, 255};
    Renderer* renderer = nullptr;
    MovableModelBehavior movableBehavior;
    ResizableModelBehavior resizableBehavior;
public:
    void SetRenderFromCenter(bool renderFromCenter);

    bool GetRenderFromCenter() const;

    EllipseModel();

    void SetFill(bool fill);

    [[nodiscard]] bool GetFill() const;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(size_t id) override;

    const size_t & GetModelId() override;

    [[nodiscard]] const glm::vec4 &GetAbsolutePosition() const override;

    void SetPosition(const glm::vec4 &position, bool emit = true) override;

    void SetTranslate(const glm::vec4 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec4 & GetTranslate() const override;

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

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void ResetViewport() override;

    void SetColor(const glm::ivec4 &color);

    const glm::ivec4 & GetColor();

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    const glm::vec4 & GetViewportSize() override;

    const glm::vec4 & GetViewportPosition() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

    const glm::vec4 &GetPosition() const override;

};


#endif //LII_ELLIPSEMODEL_H
