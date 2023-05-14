//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RECTANGLEMODEL_H
#define LII_RECTANGLEMODEL_H
#include "Movable.h"
#include "Resizable.h"
#include "MovableModelBehavior.h"
#include "ResizableModelBehavior.h"
#include "RenderingModel.h"
#include "DefaultViewport.h"
#include "Renderer.h"

class RectangleModel : public Movable, public Resizable, public RenderingModel
{
private:
    bool visible = true;
    MovableModelBehavior movableBehavior;
    ResizableModelBehavior resizableBehavior;
    Renderer* renderer = nullptr;
    glm::ivec4 color{255, 255, 255, 255};
    DefaultViewport viewPort;
    bool fill = true;
    size_t id = -1;
    float thickness = 1.0f;
public:
    RectangleModel();

    [[nodiscard]] const DefaultViewport& GetViewPort() const;

    bool IsViewPortSet();

    void ResetViewport();

    void SetFill(bool fill);
    [[nodiscard]] const bool &GetFill() const;

    void SetColor(const glm::vec4 &color);
    [[nodiscard]] const glm::ivec4 & GetColor() const;

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

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(size_t id) override;

    const size_t & GetModelId() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;

    void SetThickness(float thickness);

    float GetThickness() const;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_RECTANGLEMODEL_H
