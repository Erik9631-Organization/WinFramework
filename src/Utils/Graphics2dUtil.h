//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include <Windows.h>
#include <gdiplus.h>
#include "GraphicsScaling.h"
#include "Renderable.h"

class Graphics2dUtil
{
public:
    Graphics2dUtil(Gdiplus::PointF& associatedPosition);
    Graphics2dUtil(Gdiplus::PointF& associatedPosition, Gdiplus::SizeF& associatedSize);

    bool IsDrawFromCenterX() const;
    void SetDrawFromCenterX(bool drawFromCenterX);
    bool IsDrawFromCenterY() const;
    void SetDrawFromCenterY(bool drawFromCenterY);

    GraphicsScaling GetScalingTypeX() const;
    void SetScalingTypeX(GraphicsScaling scalingTypeX);
    GraphicsScaling GetScalingTypeY() const;
    void SetScalingTypeY(GraphicsScaling scalingTypeY);
    GraphicsScaling GetScalingTypeWidth() const;
    void SetScalingTypeWidth(GraphicsScaling scalingTypeWidth);
    GraphicsScaling GetScalingTypeHeight() const;
    void SetScalingTypeHeight(GraphicsScaling scalingTypeHeight);

    void UpdateAssociatedParameters(Gdiplus::PointF parentPosition, Gdiplus::SizeF parentSize);

    Gdiplus::SizeF& GetSize();
    Gdiplus::PointF& GetPosition();
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();

private:
    bool drawFromCenterX = false;
    bool drawFromCenterY = false;

    GraphicsScaling scalingTypeX = Percentual;
    GraphicsScaling scalingTypeY = Percentual;
    GraphicsScaling scalingTypeWidth = Percentual;
    GraphicsScaling scalingTypeHeight = Percentual;

    Gdiplus::SizeF& associatedSize;
    Gdiplus::PointF& associatedPosition;

    Gdiplus::SizeF calculatedSize;
    Gdiplus::PointF calculatedPosition;

    Gdiplus::SizeF defaultSize;
};


#endif //GRAPHICS_GRAPHICS2DUTIL_H
