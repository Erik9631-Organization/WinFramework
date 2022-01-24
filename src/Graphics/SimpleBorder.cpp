#include "SimpleBorder.h"
#include "RenderEventInfo.h"
#include "GraphicsScaling.h"
#include "CoreWindowFrame.h"


SimpleBorder::SimpleBorder() :
    renderBehavior(*this),
    reflectionContainer(*this),
    graphicsUtil(position, size)
{
	//Set up meta data
	reflectionContainer.RegisterMethod("border-color", "SetColor", &SimpleBorder::SetColor);
	reflectionContainer.RegisterMethod("border-style", "SetBorderStyle", &SimpleBorder::SetBorderStyle);
	reflectionContainer.RegisterMethod("border-thickness", "SetThickness", &SimpleBorder::SetThickness);


    position.X = 0.0f;
    position.Y = 0.0f;

	size.Width = 1.0f;
	size.Height = 1.0f;


	brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
	pen = new Gdiplus::Pen(brush);
	pen->SetWidth(0.01f);
}


SimpleBorder::~SimpleBorder()
{
	delete pen;
	delete brush;
}

void SimpleBorder::SetColor(Gdiplus::Color color)
{
	this->color = color;
	pen->SetColor(color);
}

Gdiplus::Color SimpleBorder::GetColor()
{
	return color;
}

void SimpleBorder::SetBorderStyle(Gdiplus::DashStyle style)
{
	pen->SetDashStyle(style);
}

void SimpleBorder::SetThickness(float thickness)
{
	pen->SetWidth(thickness / 100);
}

void SimpleBorder::DrawFromCenterX(bool state)
{
    graphicsUtil.SetCalculateFromCenterX(state);
}

void SimpleBorder::DrawFromCenterY(bool state)
{
    graphicsUtil.SetCalculateFromCenterY(state);
}

void SimpleBorder::OnRender(RenderEventInfo e)
{

    Gdiplus::PointF parentPosition = Gdiplus::PointF((float)e.GetParentPosition().X, (float)e.GetParentPosition().Y);
    Gdiplus::SizeF parentSize = Gdiplus::SizeF((float)e.GetParentSize().Width, (float)e.GetParentSize().Height);
    graphicsUtil.UpdateAssociatedParameters(parentPosition, parentSize);

	e.GetGraphics()->DrawRectangle(pen, graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
	renderBehavior.OnRender(e);
}

void SimpleBorder::Repaint()
{

}

void SimpleBorder::AddRenderable(Renderable& renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void SimpleBorder::RemoveRenderable(Renderable& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> SimpleBorder::GetRenderables()
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

Gdiplus::SizeF SimpleBorder::GetSize()
{
	return this->size;
}

Gdiplus::PointF SimpleBorder::GetPosition()
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

void SimpleBorder::SetSize(Gdiplus::SizeF size)
{
    this->size = size;
}

void SimpleBorder::SetPosition(Gdiplus::PointF point)
{
    this->position = point;
}

void SimpleBorder::SetX(float x)
{
    this->position.X = x;
}

void SimpleBorder::SetY(float y)
{
    this->position.Y = y;
}

void SimpleBorder::SetWidth(float width)
{
    this->size.Width = width;
}

void SimpleBorder::SetHeight(float height)
{
    this->size.Height = height;
}

float SimpleBorder::GetX()
{
    return position.X;
}

float SimpleBorder::GetY()
{
    return position.Y;
}

float SimpleBorder::GetWidth()
{
    return size.Width;
}

float SimpleBorder::GetHeight()
{
    return size.Height;
}
