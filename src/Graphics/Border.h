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

    void OnViewportSizeChanged(const ViewportEventInfo &event) override;

    void OnViewportPositionChanged(const ViewportEventInfo &event) override;

    void OnViewportReset(const ViewportEventInfo &event) override;

private:
    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
};


#endif //LII_BORDER_H
