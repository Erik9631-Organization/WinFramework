//
// Created by erik9 on 4/19/2023.
//

#ifndef LII_RADIOCIRCLE_H
#define LII_RADIOCIRCLE_H


#include "Appearance.h"
#include "EllipseProxy.h"
#include "DefaultRelativeZIndex.h"
#include "ScalingUtil2D.h"

class RadioCircle : public Appearance, public Movable
{
private:
    EllipseProxy border;
    EllipseProxy fill;
    ScalingUtil2D scaler;
    UiElement& element;

    float radius = 50;
    float padding = 0.7f;
    void UpdateGraphics();
    glm::vec4 position = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("None"), 0};
    std::vector<MoveSubscriber*> moveSubscribers;
public:
    void SetFillEnabled(bool state);

    void SetBorderColor(const glm::ivec4 &color);

    void SetFillColor(const glm::ivec4 &color);

    ScalingUtil2D& GetScales();

    float GetRelativeZIndex() override;

    void SetRelativeZIndex(float relativeZIndex) override;

    void SetRadius(float radius);

    void SetPadding(float padding);

    [[nodiscard]] float GetPadding() const;

    [[nodiscard]] float GetRadius() const;

    explicit RadioCircle(UiElement &element);

    void OnMounted(Presenter &presenter, UiElement &element) override;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;

    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 &GetAbsolutePosition() override;

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

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void SetVisible(bool state) override;
};


#endif //LII_RADIOCIRCLE_H
