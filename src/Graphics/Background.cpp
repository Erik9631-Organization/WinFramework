#include "Background.h"
#include "RenderEventInfo.h"
#include "WindowsCore.h"
#include "RenderingPool.h"


Background::Background() : renderBehavior(*this), reflectionContainer(*this), graphicsUtil(position, size)
{
    position = {0.0f, 0.0f};
    size = {1.0f, 1.0f};

    reflectionContainer.RegisterMethod<Vector3>("background-color", "SetColor", &Background::SetColor);
    reflectionContainer.RegisterMethod<Vector4>("background-colorRGBA", "SetColor", &Background::SetColor);
    reflectionContainer.RegisterMethod("get-background-color", "SetColor", &Background::GetColor);
}

Background::~Background()
{
}

void Background::SetColor(Vector3 color)
{
    currentColor = {color.GetX(), color.GetY(), color.GetZ(), 255};
}

Vector3 Background::GetColor()
{
    return {currentColor.GetX(), currentColor.GetY(), currentColor.GetZ()};
}

void Background::SetWidth(float width)
{
    size.x = width;
}

void Background::SetHeight(float height)
{
    size.y = height;
}

void Background::SetX (float x)
{
    position.x = x;
}

void Background::SetY(float y)
{
    position.y = y;
}

float Background::GetWidth()
{
    return size.x;
}

float Background::GetHeight()
{
    return size.y;
}

float Background::GetX()
{
    return position.x;
}

float Background::GetY()
{
    return position.y;
}

void Background::OnRenderSync(RenderEventInfo e)
{
    Renderer& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());
    renderer.SetColor(currentColor);
    renderer.FillRectangle(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
}

void Background::Repaint()
{

}

void Background::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void Background::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> Background::GetRenderables()
{
    return std::vector<std::reference_wrapper<RenderCommander>>();
}

bool Background::HasMethod(std::string method)
{
    return reflectionContainer.HasMethod(method);
}

ReflectionContainer<Background>& Background::GetReflectionContainer()
{
    return reflectionContainer;
}

GraphicsScaling Background::GetScalingTypeX() const
{
    return graphicsUtil.GetScalingTypeX();
}

void Background::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    graphicsUtil.SetScalingTypeX(scalingTypeX);
}

GraphicsScaling Background::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void Background::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    graphicsUtil.SetScalingTypeY(scalingTypeY);
}

GraphicsScaling Background::GetScalingTypeWidth() const
{
    return graphicsUtil.GetScalingTypeWidth();
}

void Background::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    graphicsUtil.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling Background::GetScalingTypeHeight() const
{
    return graphicsUtil.GetScalingTypeHeight();
}

void Background::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    graphicsUtil.SetScalingTypeHeight(scalingTypeHeight);
}

glm::vec2 Background::GetSize()
{
    return size;
}

glm::vec2 Background::GetPosition()
{
    return position;
}

void Background::SetPosition(const glm::vec2 &position)
{
    this->position = position;
}

void Background::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

void Background::SetColor(Vector4 color)
{
    this->currentColor = color;
}

Vector4 Background::GetColorRGBA()
{
    return currentColor;
}

void Background::OnSync(const DrawData &data)
{
    if(data.GetDataType() != DrawData::drawData2D)
        return;
    const DrawData2D& syncedData = static_cast<const DrawData2D&>(data);
    drawData = DrawData2D(syncedData);
}
