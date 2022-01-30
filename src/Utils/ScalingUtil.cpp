//
// Created by Erik on 1/13/2022.
//

#include "ScalingUtil.h"
#include "Vector2DScaler.h"


ScalingUtil::ScalingUtil(Vector2 &associatedPosition) : ScalingUtil(associatedPosition, defaultSize)
{

}


ScalingUtil::ScalingUtil(Vector2 &associatedPosition, Vector2 &associatedSize) :
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

void ScalingUtil::CreateRatio(Vector2 parentPosition, Vector2 parentSize)
{
    Vector2DScaler positionScaler = Vector2DScaler(parentSize, scalingTypeX, scalingTypeY);
    Vector2DScaler sizeScaler = Vector2DScaler(parentSize, scalingTypeWidth, scalingTypeHeight);

    Vector2 scaledPosition = positionScaler.GetScaledValues(associatedPosition);
    Vector2 scaledSize = sizeScaler.GetScaledValues(associatedSize);


    if (calculateFromCenterX)
        scaledPosition.SetX(scaledPosition.GetX() - (scaledSize.GetX() / 2.0f));
    if(calculateFromCenterY)
        scaledPosition.SetY(scaledPosition.GetY() - (scaledSize.GetY() / 2.0f));

    calculatedSize.SetX(scaledSize.GetX());
    calculatedSize.SetY(scaledSize.GetY());

    calculatedPosition.SetX(scaledPosition.GetX());
    calculatedPosition.SetY(scaledPosition.GetY());
}

Vector2 ScalingUtil::GetSize()
{
    return calculatedSize;
}

Vector2 ScalingUtil::GetPosition()
{
    return calculatedPosition;
}

float ScalingUtil::GetX()
{
    return calculatedPosition.GetX();
}

float ScalingUtil::GetY()
{
    return calculatedPosition.GetY();
}

float ScalingUtil::GetWidth()
{
    return calculatedSize.GetX();
}

float ScalingUtil::GetHeight()
{
    return calculatedSize.GetY();
}
