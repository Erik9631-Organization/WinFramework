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
#include "Vector4.h"

class RectangleModel : public Movable, public Resizable, public RenderingModel
{
private:
    MovableModelBehavior movableBehavior;
    ResizableModelBehavior resizableBehavior;
    RenderingProvider* rendereringProvider;
    Vector4 color{255, 255, 255, 255};
    bool fill = true;
    size_t id = -1;

public:
    void SetFill(bool fill);
    const bool &GetFill() const;

    void SetColor(const Vector4& color );
    const Vector4& GetColor() const;

    glm::vec2 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec2 GetAbsolutePosition() override;

    void SetPosition(glm::vec2 position, bool emit) override;

    void SetPosition(glm::vec2 position) override;

    void SetPosition(float x, float y, bool emit) override;

    void SetPosition(float x, float y) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec2 offset, bool emit) override;

    void SetTranslate(glm::vec2 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec2 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    glm::vec2 GetSize() override;

    float GetWidth() override;

    float GetHeight() override;

    void SetSize(glm::vec2 size, bool emit) override;

    void SetSize(glm::vec2 size) override;

    void SetSize(float width, float height, bool emit) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width, bool emit) override;

    void SetWidth(float width) override;

    void SetHeight(float height, bool emit) override;

    void SetHeight(float height) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void Redraw() override;

    void SetRenderingProvider(RenderingProvider *renderer) override;

    void SetAssociatedModelId(unsigned long long int id) override;

    size_t & GetModelId() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;
};


#endif //LII_RECTANGLEMODEL_H
