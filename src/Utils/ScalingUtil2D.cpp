//
// Created by Erik on 1/13/2022.
//

#include "ScalingUtil2D.h"
#include "Vector2DScaler.h"

ScalingUtil2D::ScalingUtil2D(const glm::vec4 &viewPortPosition, const glm::vec4 &viewPortSize) :
        viewPortSize(viewPortSize),
        viewPortPosition(viewPortPosition),
        positionScaler(viewPortSize),
        sizeScaler(viewPortSize)
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

void ScalingUtil2D::Scale(const glm::vec4 &inputVector)
{
    positionScaler.SetScalingTypeX(scalingTypeX);
    positionScaler.SetScalingTypeY(scalingTypeY);
    sizeScaler.SetScalingTypeX(scalingTypeWidth);
    sizeScaler.SetScalingTypeY(scalingTypeHeight);

    auto scaledPosition = positionScaler.GetScaledValues(inputVector);
    auto scaledSize = sizeScaler.GetScaledValues(inputVector);


    if (calculateFromCenterX)
        scaledPosition.x = scaledPosition.x + (viewPortSize.x / 2.0f);
    if(calculateFromCenterY)
        scaledPosition.y = scaledPosition.y + (viewPortSize.y / 2.0f);

    calculatedSize.x = scaledSize.x;
    calculatedSize.y = scaledSize.y;

    calculatedPosition = {scaledPosition.x + viewPortPosition.x,
                          scaledPosition.y + viewPortPosition.y, viewPortPosition.z, viewPortPosition.w};
}

const glm::vec4 & ScalingUtil2D::GetSize()
{
    return calculatedSize;
}

const glm::vec4 & ScalingUtil2D::GetPosition()
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
