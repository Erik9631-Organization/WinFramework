//
// Created by erik9 on 2/19/2023.
//

#ifndef LII_BORDER_H
#define LII_BORDER_H
#include "Appearance.h"
#include "RectangleProxy.h"
#include "DefaultRelativeZIndex.h"
#include <memory>

class Border : public Appearance
{
private:
    UiElement& associatedElement;
    Presenter* presenter = nullptr;
    RectangleProxy rectangleProxy;
    glm::vec3 relativeZIndex = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("BorderIndex")};
public:
    ~Border() override;

    explicit Border(UiElement& element);
    void OnMounted(Presenter &presenter, UiElement &element) override;
    void OnMove(EventMoveInfo e) override;
    void OnResize(EventResizeInfo e) override;
    void SetColor(glm::ivec4 color);

    void SetVisible(bool state) override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec4 & GetViewportSize() override;

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

private:
    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
};


#endif //LII_BORDER_H
