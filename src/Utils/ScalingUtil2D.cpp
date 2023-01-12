//
// Created by Erik on 1/13/2022.
//

#include "ScalingUtil2D.h"
#include "Vector2DScaler.h"


ScalingUtil2D::ScalingUtil2D(glm::vec4 &associatedPosition) : ScalingUtil2D(associatedPosition, defaultSize)
{

}


ScalingUtil2D::ScalingUtil2D(glm::vec4 &associatedPosition, glm::vec4 &associatedSize) :
    associatedPosition(associatedPosition),
    associatedSize(associatedSize)
{

}

bool ScalingUtil2D::IsCalculatingFromCenterX() const
{
    return calculateFromCenterX;
}

void ScalingUtil2D::SetCalculateFromCenterX(bool calculateFromCenterX)
{
    ScalingUtil2D::calculateFromCenterX = calculateFromCenterX;
}

bool ScalingUtil2D::IsCalculateFromCenterY() const
{
    return calculateFromCenterY;
}

void ScalingUtil2D::SetCalculateFromCenterY(bool calculateFromCenterY)
{
    ScalingUtil2D::calculateFromCenterY = calculateFromCenterY;
}

GraphicsScaling ScalingUtil2D::GetScalingTypeX() const
{
    return scalingTypeX;
}

void ScalingUtil2D::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    ScalingUtil2D::scalingTypeX = scalingTypeX;
}

GraphicsScaling ScalingUtil2D::GetScalingTypeY() const
{
    return scalingTypeY;
}

void ScalingUtil2D::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    ScalingUtil2D::scalingTypeY = scalingTypeY;
}

GraphicsScaling ScalingUtil2D::GetScalingTypeWidth() const
{
    return scalingTypeWidth;
}

void ScalingUtil2D::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    ScalingUtil2D::scalingTypeWidth = scalingTypeWidth;
}

GraphicsScaling ScalingUtil2D::GetScalingTypeHeight() const
{
    return scalingTypeHeight;
}

void ScalingUtil2D::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    ScalingUtil2D::scalingTypeHeight = scalingTypeHeight;
}

void ScalingUtil2D::CreateRatio(const glm::vec4 &parentPosition, const glm::vec4 &parentSize)
{
    Vector2DScaler positionScaler = Vector2DScaler(parentSize, scalingTypeX, scalingTypeY);
    Vector2DScaler sizeScaler = Vector2DScaler(parentSize, scalingTypeWidth, scalingTypeHeight);

    auto scaledPosition = positionScaler.GetScaledValues(associatedPosition);
    auto scaledSize = sizeScaler.GetScaledValues(associatedSize);


    if (calculateFromCenterX)
        scaledPosition.x = scaledPosition.x - (scaledSize.x / 2.0f);
    if(calculateFromCenterY)
        scaledPosition.y = scaledPosition.y - (scaledSize.y / 2.0f);

    calculatedSize.x = scaledSize.x;
    calculatedSize.y = scaledSize.y;

    calculatedPosition.x = scaledPosition.x;
    calculatedPosition.y = scaledPosition.y;
}

glm::vec4 ScalingUtil2D::GetSize()
{
    return calculatedSize;
}

glm::vec4 ScalingUtil2D::GetPosition()
{
    return calculatedPosition;
}

float ScalingUtil2D::GetX()
{
    return calculatedPosition.x;
}

float ScalingUtil2D::GetY()
{
    return calculatedPosition.y;
}

float ScalingUtil2D::GetWidth()
{
    return calculatedSize.x;
}

float ScalingUtil2D::GetHeight()
{
    return calculatedSize.y;
}
