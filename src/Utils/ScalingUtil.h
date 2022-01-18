//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include <Windows.h>
#include <gdiplus.h>
#include "GraphicsScaling.h"
#include "Renderable.h"

class ScalingUtil
{
public:
    ScalingUtil(Gdiplus::PointF& associatedPosition);
    ScalingUtil(Gdiplus::PointF& associatedPosition, Gdiplus::SizeF& associatedSize);

    bool IsCalculatingFromCenterX() const;
    void SetCalculateFromCenterX(bool calculateFromCenterX);
    bool IsCalculateFromCenterY() const;
    void SetCalculateFromCenterY(bool calculateFromCenterY);

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
    bool calculateFromCenterX = false;
    bool calculateFromCenterY = false;

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
