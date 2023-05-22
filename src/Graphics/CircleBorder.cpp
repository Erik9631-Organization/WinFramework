#include "CircleBorder.h"
#include "RenderEventInfo.h"
#include "DrawData.h"
#include "RenderingPool.h"

CircleBorder::CircleBorder() : renderBehavior(*this), graphicsUtil(position, size)
{
    thickness = 1.0f / 100.0f;
    color = {0, 0, 0, 255};
}

CircleBorder::~CircleBorder()
{

}

void CircleBorder::OnRenderSync(RenderEventInfo e)
{
    ShapeRenderer& renderer = e.GetRenderer()->Acquire(*this);

    graphicsUtil.Scale(drawData.GetSize());
    renderer.SetThickness(thickness);
    renderer.SetColor(color);
    renderer.DrawEllipse(graphicsUtil.GetPosition(), graphicsUtil.GetSize(), true);
    renderBehavior.OnRenderSync(e);
}

void CircleBorder::Repaint()
{
}

void CircleBorder::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void CircleBorder::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

void CircleBorder::SetDiameter(float diameter)
{
    this->size = {diameter, diameter, 0, 0};
    this->diameter = diameter;
}

std::vector<std::reference_wrapper<RenderCommander>> CircleBorder::GetRenderables()
{
    return renderBehavior.GetRenderables();
}

void CircleBorder::SetThickness(float thickness)
{
    this->thickness = thickness / 100;
}

float CircleBorder::GetDiameter()
{
    return diameter;
}
float CircleBorder::GetThickness()
{
    return thickness;
}

void CircleBorder::SetColor(glm::ivec3 color)
{
    this->color = {color.x, color.y, color.z, 255};
}

GraphicsScaling CircleBorder::GetScalingTypeX() const
{
    return graphicsUtil.GetScalingTypeX();
}

void CircleBorder::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    graphicsUtil.SetUnitTypePosX(scalingTypeX);
}

GraphicsScaling CircleBorder::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void CircleBorder::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    return graphicsUtil.SetUnitTypePosY(scalingTypeY);
}

GraphicsScaling CircleBorder::GetScalingTypeWidth() const
{
    return graphicsUtil.GetScalingTypeWidth();
}

void CircleBorder::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    graphicsUtil.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling CircleBorder::GetScalingTypeHeight() const
{
    return graphicsUtil.GetScalingTypeHeight();
}

void CircleBorder::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    graphicsUtil.SetScalingTypeHeight(scalingTypeHeight);
}

bool CircleBorder::IsDrawFromCenterY() const
{
    return graphicsUtil.IsCalculateFromCenterY();
}

void CircleBorder::SetDrawFromCenterY(bool drawFromCenterY)
{
    graphicsUtil.SetCalculateFromCenterY(drawFromCenterY);
}

bool CircleBorder::IsDrawFromCenterX() const
{
    return graphicsUtil.IsCalculatingFromCenterX();
}

void CircleBorder::SetDrawFromCenterX(bool drawFromCenterX)
{
    graphicsUtil.SetCalculateFromCenterX(drawFromCenterX);
}

glm::vec4 CircleBorder::GetPosition()
{
    return position;
}

void CircleBorder::SetPosition(glm::vec4 point)
{
    this->position = point;
}

void CircleBorder::SetX(float x)
{
    position.x = x;
}

void CircleBorder::SetY(float y)
{
    position.y = y;
}

float CircleBorder::GetX()
{
    return position.x;
}

float CircleBorder::GetY()
{
    return position.y;
}

void CircleBorder::SetColor(glm::ivec4 color)
{
    this->color = color;
}

void CircleBorder::OnSync(const DrawData &data)
{
    if(data.GetDataType() != DrawData::drawData2D)
        return;

    drawData = DrawData2D(static_cast<const DrawData2D&>(data));
}
