//
// Created by Erik on 1/12/2022.
//

#ifndef GRAPHICS_VECTOR2DSCALER_H
#define GRAPHICS_VECTOR2DSCALER_H
#include <glm.hpp>
#include "GraphicsScaling.h"

class Vector2DScaler
{
private:
    glm::vec2 parentVector{0};
    GraphicsScaling scalingTypeX;
    GraphicsScaling scalingTypeY;
public:
    Vector2DScaler(const glm::vec2 &parentVector, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY);
    Vector2DScaler(const glm::vec2 &parentVector);

    GraphicsScaling GetScalingTypeX() const;

    void SetScalingTypeX(GraphicsScaling scalingTypeX);

    GraphicsScaling GetScalingTypeY() const;

    void SetScalingTypeY(GraphicsScaling scalingTypeY);
    glm::vec2 GetScaledValues(const glm::vec2 &input);


};


#endif //GRAPHICS_VECTOR2DSCALER_H
