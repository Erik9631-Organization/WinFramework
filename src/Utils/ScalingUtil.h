//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include <Windows.h>
#include <gdiplus.h>
#include "GraphicsScaling.h"
#include "api/RenderCommander.h"
#include "Vector2.h"

class ScalingUtil
{
public:
    ScalingUtil(Vector2 &associatedPosition);
    ScalingUtil(Vector2 &associatedPosition, Vector2 &associatedSize);

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

    void CreateRatio(Vector2 parentPosition, Vector2 parentSize);

    Vector2 GetSize();
    Vector2 GetPosition();
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

    Vector2& associatedSize;
    Vector2& associatedPosition;

    Vector2 calculatedSize;
    Vector2 calculatedPosition;

    Vector2 defaultSize;
};


#endif //GRAPHICS_GRAPHICS2DUTIL_H
