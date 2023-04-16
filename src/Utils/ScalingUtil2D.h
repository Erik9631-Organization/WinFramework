//
// Created by Erik on 1/13/2022.
//

#ifndef GRAPHICS_GRAPHICS2DUTIL_H
#define GRAPHICS_GRAPHICS2DUTIL_H
#include "GraphicsScaling.h"
#include "RenderCommander.h"
#include "Vector2DScaler.h"

class ScalingUtil2D
{
public:
    ScalingUtil2D(const glm::vec4 &viewPortPosition, const glm::vec4 &viewPortSize);

    bool IsCalculatingFromCenterX() const;
    void SetCalculateFromCenterX(bool calculateFromCenterX);
    bool IsCalculateFromCenterY() const;
    void SetCalculateFromCenterY(bool calculateFromCenterY);

    [[nodiscard]] GraphicsScaling GetScalingTypeX() const;
    void SetScalingTypeX(GraphicsScaling scalingTypeX);
    [[nodiscard]] GraphicsScaling GetScalingTypeY() const;
    void SetScalingTypeY(GraphicsScaling scalingTypeY);
    [[nodiscard]] GraphicsScaling GetScalingTypeWidth() const;
    void SetScalingTypeWidth(GraphicsScaling scalingTypeWidth);
    [[nodiscard]] GraphicsScaling GetScalingTypeHeight() const;
    void SetScalingTypeHeight(GraphicsScaling scalingTypeHeight);

    void Scale(const glm::vec4 &translationVector);

    const glm::vec4 & GetSize();
    const glm::vec4 & GetPosition();
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();

private:
    bool calculateFromCenterX = false;
    bool calculateFromCenterY = false;

    GraphicsScaling scalingTypeX = Decimal;
    GraphicsScaling scalingTypeY = Decimal;
    GraphicsScaling scalingTypeWidth = Decimal;
    GraphicsScaling scalingTypeHeight = Decimal;

    const glm::vec4& viewPortPosition;
    const glm::vec4& viewPortSize;

    glm::vec4 calculatedSize{0};
    glm::vec4 calculatedPosition{0};

    Vector2DScaler positionScaler;
    Vector2DScaler sizeScaler;
};


#endif //GRAPHICS_GRAPHICS2DUTIL_H
