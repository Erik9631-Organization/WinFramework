//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include "GraphicsScaling.h"
#include "api/RenderCommander.h"
#include "vec2.hpp"

class ScalingUtil2D
{
public:
    ScalingUtil2D(glm::vec4 &associatedPosition);
    ScalingUtil2D(glm::vec4 &associatedPosition, glm::vec4 &associatedSize);

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

    void CreateRatio(const glm::vec4 &parentPosition, const glm::vec4 &parentSize);

    glm::vec4 GetSize();
    glm::vec4 GetPosition();
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

    glm::vec4& associatedSize;
    glm::vec4& associatedPosition;

    glm::vec4 calculatedSize{0};
    glm::vec4 calculatedPosition{0};

    glm::vec4 defaultSize{0};
};


#endif //GRAPHICS_GRAPHICS2DUTIL_H
