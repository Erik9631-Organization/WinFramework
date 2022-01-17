//
// Created by Erik on 1/13/2022.
//

#include "Graphics2dUtil.h"
#include "Vector2DScaler.h"


Graphics2dUtil::Graphics2dUtil(Gdiplus::PointF &associatedPosition) : Graphics2dUtil(associatedPosition, defaultSize)
{

}


Graphics2dUtil::Graphics2dUtil(Gdiplus::PointF& associatedPosition, Gdiplus::SizeF& associatedSize) :
    associatedPosition(associatedPosition),
    associatedSize(associatedSize)
{

}

bool Graphics2dUtil::IsDrawFromCenterX() const
{
    return drawFromCenterX;
}

void Graphics2dUtil::SetDrawFromCenterX(bool drawFromCenterX)
{
    Graphics2dUtil::drawFromCenterX = drawFromCenterX;
}

bool Graphics2dUtil::IsDrawFromCenterY() const
{
    return drawFromCenterY;
}

void Graphics2dUtil::SetDrawFromCenterY(bool drawFromCenterY)
{
    Graphics2dUtil::drawFromCenterY = drawFromCenterY;
}

GraphicsScaling Graphics2dUtil::GetScalingTypeX() const
{
    return scalingTypeX;
}

void Graphics2dUtil::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    Graphics2dUtil::scalingTypeX = scalingTypeX;
}

GraphicsScaling Graphics2dUtil::GetScalingTypeY() const
{
    return scalingTypeY;
}

void Graphics2dUtil::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    Graphics2dUtil::scalingTypeY = scalingTypeY;
}

GraphicsScaling Graphics2dUtil::GetScalingTypeWidth() const
{
    return scalingTypeWidth;
}

void Graphics2dUtil::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    Graphics2dUtil::scalingTypeWidth = scalingTypeWidth;
}

GraphicsScaling Graphics2dUtil::GetScalingTypeHeight() const
{
    return scalingTypeHeight;
}

void Graphics2dUtil::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    Graphics2dUtil::scalingTypeHeight = scalingTypeHeight;
}

void Graphics2dUtil::UpdateAssociatedParameters(Gdiplus::PointF parentPosition, Gdiplus::SizeF parentSize)
{
    Vector2DScaler positionScaler = Vector2DScaler(parentSize, scalingTypeX, scalingTypeY);
    Vector2DScaler sizeScaler = Vector2DScaler(parentSize, scalingTypeWidth, scalingTypeHeight);

    Vector2d scaledPosition = positionScaler.GetScaledValues(associatedPosition);
    Vector2d scaledSize = sizeScaler.GetScaledValues(associatedSize);


    if (drawFromCenterX)
        scaledPosition.SetX(scaledPosition.GetX() - (scaledSize.GetX() / 2.0f));
    if(drawFromCenterY)
        scaledPosition.SetY(scaledPosition.GetY() - (scaledSize.GetY() / 2.0f));

    calculatedSize.Width = scaledSize.GetX();
    calculatedSize.Height = scaledSize.GetY();

    calculatedPosition.X = scaledPosition.GetX();
    calculatedPosition.Y = scaledPosition.GetY();
}

Gdiplus::SizeF &Graphics2dUtil::GetSize()
{
    return calculatedSize;
}

Gdiplus::PointF &Graphics2dUtil::GetPosition()
{
    return calculatedPosition;
}

float Graphics2dUtil::GetX()
{
    return calculatedPosition.X;
}

float Graphics2dUtil::GetY()
{
    return calculatedPosition.Y;
}

float Graphics2dUtil::GetWidth()
{
    return calculatedSize.Width;
}

float Graphics2dUtil::GetHeight()
{
    return calculatedSize.Height;
}
