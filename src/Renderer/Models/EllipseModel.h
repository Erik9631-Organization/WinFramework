//
// Created by erik9 on 4/18/2023.
//

#ifndef LII_ELLIPSEMODEL_H
#define LII_ELLIPSEMODEL_H


#include "RenderingModel.h"
#include "DefaultViewport.h"
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
    DefaultViewport viewPort;
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

    void ResetViewport() override;

    void SetColor(const glm::ivec4 &color);

    const glm::ivec4 & GetColor();

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void AddViewportSubscriber(ViewportSubscriber &subscriber) override;

    void RemoveViewportSubscriber(ViewportSubscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const ViewportEventInfo &event) override;

    void NotifyOnViewportPositionChanged(const ViewportEventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const ViewportEventInfo &event) override;

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

};


#endif //LII_ELLIPSEMODEL_H
