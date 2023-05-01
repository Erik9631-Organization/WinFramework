#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "ReflectionContainer.h"
#include "ScalingUtil2D.h"
#include "DrawData2D.h"
#include "Appearance.h"
#include "RectangleProxy.h"
#include "DefaultRelativeZIndex.h"

/**
 * A background renderable. Displays a backround with the defined color in the entire canvas of the component.
 * Supported properties:
 * background-color, args: Gdiplus::Color, return void
 * get-background-color, return Gdiplus::Color
 */

//TODO const correctness---Mark functions that return const as const functions

class Background : public Appearance
{
private:
    Presenter* presenter = nullptr;
    RectangleProxy rectangleProxy;
    UiElement& associatedElement;
    glm::vec3 relativeZIndex = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("BackgroundIndex")};
public:
    explicit Background(UiElement& element);
    ~Background() override;

    const glm::ivec4& GetColor();

    void SetColor(glm::ivec4 color);

    void OnMounted(Presenter &presenter, UiElement& element) override;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;

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

    void OnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void OnViewportPositionChanged(const Viewport2EventInfo &event) override;

    void OnViewportReset(const Viewport2EventInfo &event) override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

private:
    float GetRelativeZIndex() override;

    void SetRelativeZIndex(float relativeZIndex) override;
};
