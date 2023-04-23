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
#include "ModelViewport.h"
#include "Renderer.h"

class RectangleModel : public Movable, public Resizable, public RenderingModel
{
private:
    bool visible = true;
    MovableModelBehavior movableBehavior;
    ResizableModelBehavior resizableBehavior;
    Renderer* renderer = nullptr;
    glm::ivec4 color{255, 255, 255, 255};
    ModelViewport viewPort;
    bool fill = true;
    size_t id = -1;
    float thickness = 1.0f;
public:
    RectangleModel();

    [[nodiscard]] const ModelViewport& GetViewPort() const;

    bool IsViewPortSet();

    void ResetViewPort();

    void SetFill(bool fill);
    [[nodiscard]] const bool &GetFill() const;

    void SetColor(const glm::vec4 &color);
    [[nodiscard]] const glm::ivec4 & GetColor() const;

    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

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

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    const glm::vec4 & GetSize() override;

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

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(long long int id) override;

    const size_t & GetModelId() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;

    void SetThickness(float thickness);
    float GetThickness() const;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewPortSize(const glm::vec4 &vec4) override;

    void SetViewPortPosition(const glm::vec4 &vec4) override;

    glm::vec4 &GetViewPortSize() override;

    glm::vec4 &GetViewPortPosition() override;
};


#endif //LII_RECTANGLEMODEL_H
