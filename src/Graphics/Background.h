#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "ReflectionContainer.h"
#include "ScalingUtil2D.h"
#include "DrawData2D.h"
#include "Appearance.h"
#include "RectangleProxy.h"

/**
 * A background renderable. Displays a backround with the defined color in the entire canvas of the component.
 * Supported properties:
 * background-color, args: Gdiplus::Color, return void
 * get-background-color, return Gdiplus::Color
 */
class Background : public Appearance
{
private:
    Presenter* presenter = nullptr;
    std::unique_ptr<RectangleProxy> rectangleProxy;

public:
    void SetColor(glm::ivec4 color);

	Background(UiElement& element);

    void OnMounted(Presenter &presenter, UiElement& element) override;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;
};
