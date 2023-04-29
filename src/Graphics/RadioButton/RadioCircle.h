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
    UiElement& associatedElement;

    void Update();

    float radius = 40;
    float innerCirclePadding = 0.6f;
    void UpdateGraphics();
    glm::vec3 position = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("None")};
    std::vector<MoveSubscriber*> moveSubscribers;
public:
    ~RadioCircle() override;

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

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    void SetVisible(bool state) override;

    void ResetViewport() override;

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

    void OnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void OnViewportPositionChanged(const Viewport2EventInfo &event) override;

    void OnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_RADIOCIRCLE_H
