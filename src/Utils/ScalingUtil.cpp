//
// Created by Erik on 1/13/2022.
//

#include "ScalingUtil.h"
#include "Vector2DScaler.h"


ScalingUtil::ScalingUtil(Gdiplus::PointF &associatedPosition) : ScalingUtil(associatedPosition, defaultSize)
{

}


ScalingUtil::ScalingUtil(Gdiplus::PointF& associatedPosition, Gdiplus::SizeF& associatedSize) :
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

void ScalingUtil::UpdateAssociatedParameters(Gdiplus::PointF parentPosition, Gdiplus::SizeF parentSize)
{
    Vector2DScaler positionScaler = Vector2DScaler({parentSize.Width, parentSize.Height}, scalingTypeX, scalingTypeY);
    Vector2DScaler sizeScaler = Vector2DScaler({parentSize.Width, parentSize.Height}, scalingTypeWidth, scalingTypeHeight);

    Vector2 scaledPosition = positionScaler.GetScaledValues({associatedPosition.X, associatedPosition.Y});
    Vector2 scaledSize = sizeScaler.GetScaledValues({associatedSize.Width, associatedSize.Height});


    if (calculateFromCenterX)
        scaledPosition.SetX(scaledPosition.GetX() - (scaledSize.GetX() / 2.0f));
    if(calculateFromCenterY)
        scaledPosition.SetY(scaledPosition.GetY() - (scaledSize.GetY() / 2.0f));

    calculatedSize.Width = scaledSize.GetX();
    calculatedSize.Height = scaledSize.GetY();

    calculatedPosition.X = scaledPosition.GetX();
    calculatedPosition.Y = scaledPosition.GetY();
}

Gdiplus::SizeF &ScalingUtil::GetSize()
{
    return calculatedSize;
}

Gdiplus::PointF &ScalingUtil::GetPosition()
{
    return calculatedPosition;
}

float ScalingUtil::GetX()
{
    return calculatedPosition.X;
}

float ScalingUtil::GetY()
{
    return calculatedPosition.Y;
}

float ScalingUtil::GetWidth()
{
    return calculatedSize.Width;
}

float ScalingUtil::GetHeight()
{
    return calculatedSize.Height;
}
