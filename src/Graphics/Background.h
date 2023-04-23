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
    Resizable* viewPort = nullptr;
    glm::vec4 relativeZIndex = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("BackgroundIndex"), 0};
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

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    glm::vec4 &GetViewportSize() override;

    glm::vec4 &GetViewportPosition() override;

private:
    float GetRelativeZIndex() override;

    void SetRelativeZIndex(float relativeZIndex) override;
};
