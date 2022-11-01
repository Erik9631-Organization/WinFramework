#include "SimpleBorder.h"
#include "RenderEventInfo.h"
#include "GraphicsScaling.h"
#include "WindowsCore.h"
#include "RenderingPool.h"


SimpleBorder::SimpleBorder() :
    renderBehavior(*this),
    reflectionContainer(*this),
    graphicsUtil(position, size)
{
	//Set up meta data
	reflectionContainer.RegisterMethod<Vector3>("border-color", "SetColor", &SimpleBorder::SetColor);
	reflectionContainer.RegisterMethod<Vector4>("border-color", "SetColorRGBA", &SimpleBorder::SetColor);
	reflectionContainer.RegisterMethod("border-thickness", "SetThickness", &SimpleBorder::SetThickness);


    position = {0, 0};
    size = {1, 1};
}


SimpleBorder::~SimpleBorder()
{

}

void SimpleBorder::SetColor(Vector3 color)
{
	this->color = {color.GetX(), color.GetY(), color.GetZ(), 255};
}

Vector3 SimpleBorder::GetColor()
{
	return {color.GetX(), color.GetY(), color.GetZ()};
}


void SimpleBorder::SetThickness(float thickness)
{
	thickness = thickness / 100;
}

void SimpleBorder::DrawFromCenterX(bool state)
{
    graphicsUtil.SetCalculateFromCenterX(state);
}

void SimpleBorder::DrawFromCenterY(bool state)
{
    graphicsUtil.SetCalculateFromCenterY(state);
}

void SimpleBorder::OnRenderSync(RenderEventInfo e)
{
    Renderer& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());

    renderer.SetThickness(thickness);
    renderer.SetColor(color);
    renderer.DrawRectangle(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
    renderBehavior.OnRenderSync(e);
}

void SimpleBorder::Repaint()
{

}

void SimpleBorder::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void SimpleBorder::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> SimpleBorder::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

bool SimpleBorder::HasMethod(std::string method)
{
	return reflectionContainer.HasMethod(method);
}

ReflectionContainer<SimpleBorder>& SimpleBorder::GetReflectionContainer()
{
	return reflectionContainer;
}

glm::vec2 SimpleBorder::GetSize()
{
	return this->size;
}

glm::vec2 SimpleBorder::GetPosition()
{
	return this->position;
}

GraphicsScaling SimpleBorder::GetScalingTypeX() const
{
   return graphicsUtil.GetScalingTypeX();
}

void SimpleBorder::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    graphicsUtil.SetScalingTypeX(scalingTypeX);
}

GraphicsScaling SimpleBorder::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void SimpleBorder::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    graphicsUtil.SetScalingTypeY(scalingTypeY);
}

GraphicsScaling SimpleBorder::GetScalingTypeWidth() const
{
    return graphicsUtil.GetScalingTypeWidth();
}

void SimpleBorder::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    graphicsUtil.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling SimpleBorder::GetScalingTypeHeight() const
{
    return graphicsUtil.GetScalingTypeHeight();
}

void SimpleBorder::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    graphicsUtil.SetScalingTypeHeight(scalingTypeHeight);
}

void SimpleBorder::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

void SimpleBorder::SetPosition(const glm::vec2 &point)
{
    this->position = point;
}

void SimpleBorder::SetX(float x)
{
    this->position.x = x;
}

void SimpleBorder::SetY(float y)
{
    this->position.y = y;
}

void SimpleBorder::SetWidth(float width)
{
    this->size.x = width;
}

void SimpleBorder::SetHeight(float height)
{
    this->size.y = height;
}

float SimpleBorder::GetX()
{
    return position.x;
}

float SimpleBorder::GetY()
{
    return position.y;
}

float SimpleBorder::GetWidth()
{
    return size.x;
}

float SimpleBorder::GetHeight()
{
    return size.y;
}

void SimpleBorder::SetColor(Vector4 color)
{
    this->color = color;
}

Vector4 SimpleBorder::GetColorRGBA()
{
    return color;
}

void SimpleBorder::OnSync(const DrawData &data)
{
    drawData = DrawData2D(static_cast<const DrawData2D&>(data));
}
