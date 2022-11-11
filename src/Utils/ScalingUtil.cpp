//
// Created by Erik on 1/13/2022.
//

#include "ScalingUtil.h"
#include "Vector2DScaler.h"


ScalingUtil::ScalingUtil(glm::vec2 &associatedPosition) : ScalingUtil(associatedPosition, defaultSize)
{

}


ScalingUtil::ScalingUtil(glm::vec2 &associatedPosition, glm::vec2 &associatedSize) :
    associatedPosition(associatedPosition),
    associatedSize(associatedSize)
{

}

bool ScalingUtil::IsCalculatingFromCenterX() const
{
    return calculateFromCenterX;
}

void ScalingUtil::SetCalculateFromCenterX(bool calculateFromCenterX)
{
    ScalingUtil::calculateFromCenterX = calculateFromCenterX;
}

bool ScalingUtil::IsCalculateFromCenterY() const
{
    return calculateFromCenterY;
}

void ScalingUtil::SetCalculateFromCenterY(bool calculateFromCenterY)
{
    ScalingUtil::calculateFromCenterY = calculateFromCenterY;
}

GraphicsScaling ScalingUtil::GetScalingTypeX() const
{
    return scalingTypeX;
}

void ScalingUtil::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    ScalingUtil::scalingTypeX = scalingTypeX;
}

GraphicsScaling ScalingUtil::GetScalingTypeY() const
{
    return scalingTypeY;
}

void ScalingUtil::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    ScalingUtil::scalingTypeY = scalingTypeY;
}

GraphicsScaling ScalingUtil::GetScalingTypeWidth() const
{
    return scalingTypeWidth;
}

void ScalingUtil::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    ScalingUtil::scalingTypeWidth = scalingTypeWidth;
}

GraphicsScaling ScalingUtil::GetScalingTypeHeight() const
{
    return scalingTypeHeight;
}

void ScalingUtil::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    ScalingUtil::scalingTypeHeight = scalingTypeHeight;
}

void ScalingUtil::CreateRatio(glm::vec2 parentPosition, glm::vec2 parentSize)
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

glm::vec2 ScalingUtil::GetSize()
{
    return calculatedSize;
}

glm::vec2 ScalingUtil::GetPosition()
{
    return calculatedPosition;
}

float ScalingUtil::GetX()
{
    return calculatedPosition.x;
}

float ScalingUtil::GetY()
{
    return calculatedPosition.y;
}

float ScalingUtil::GetWidth()
{
    return calculatedSize.x;
}

float ScalingUtil::GetHeight()
{
    return calculatedSize.y;
}
