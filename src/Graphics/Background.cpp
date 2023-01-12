#include "Background.h"
#include "RenderEventInfo.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"


Background::Background() : renderBehavior(*this), reflectionContainer(*this), graphicsUtil(position, size)
{
    position = glm::vec4();
    size = {1.0f, 1.0f, 0, 0};

    reflectionContainer.RegisterMethod<glm::vec3>("background-color", "SetColor", &Background::SetColor);
    reflectionContainer.RegisterMethod<glm::vec4>("background-colorRGBA", "SetColor", &Background::SetColor);
    reflectionContainer.RegisterMethod("get-background-color", "SetColor", &Background::GetColor);
}

Background::~Background()
{
}

void Background::SetColor(glm::vec3 color)
{
    currentColor = {color.x, color.y, color.z, 255};
}

glm::vec3 Background::GetColor()
{
    return {currentColor.x, currentColor.y, currentColor.z};
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
    RenderingApi& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());
    renderer.SetColor(currentColor);
    renderer.DrawFillRectangle(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(),
                               graphicsUtil.GetHeight());
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

glm::vec4 Background::GetSize()
{
    return size;
}

glm::vec4 Background::GetPosition()
{
    return position;
}

void Background::SetPosition(glm::vec4 position)
{
    this->position = position;
}

void Background::SetSize(glm::vec4 size)
{
    this->size = size;
}

void Background::SetColor(glm::vec4 color)
{
    this->currentColor = color;
}

glm::vec3 Background::GetColorRGBA()
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
