//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include <Windows.h>
#include <gdiplus.h>
#include "GraphicsScaling.h"
#include "api/RenderCommander.h"
#include "vec2.hpp"

class ScalingUtil
{
public:
    ScalingUtil(glm::vec2 &associatedPosition);
    ScalingUtil(glm::vec2 &associatedPosition, glm::vec2 &associatedSize);

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

    void CreateRatio(const glm::vec2 &parentPosition, const glm::vec2 &parentSize);

    glm::vec2 GetSize();
    glm::vec2 GetPosition();
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

    glm::vec2& associatedSize;
    glm::vec2& associatedPosition;

    glm::vec2 calculatedSize;
    glm::vec2 calculatedPosition;

    glm::vec2 defaultSize;
};


#endif //GRAPHICS_GRAPHICS2DUTIL_H
