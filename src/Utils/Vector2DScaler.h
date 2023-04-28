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
    const glm::vec4& basis;
    GraphicsScaling scalingTypeX;
    GraphicsScaling scalingTypeY;
public:
    Vector2DScaler(const glm::vec4 &basis, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY);
    Vector2DScaler(const glm::vec4 &parentVector);

    GraphicsScaling GetScalingTypeX() const;

    void SetScalingTypeX(GraphicsScaling scalingTypeX);

    GraphicsScaling GetScalingTypeY() const;

    void SetScalingTypeY(GraphicsScaling scalingTypeY);
    glm::vec3 GetScaledValues(glm::vec3 input);
};


#endif //GRAPHICS_VECTOR2DSCALER_H
