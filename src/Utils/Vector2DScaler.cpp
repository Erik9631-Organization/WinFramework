//
// Created by Erik on 1/12/2022.
//

#include "Vector2DScaler.h"

Vector2DScaler::Vector2DScaler(const glm::vec4 &parentVector) : Vector2DScaler(parentVector, Decimal, Decimal)
{

}


Vector2DScaler::Vector2DScaler(const glm::vec4 &basis, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY) : basis(basis)
{
    this->scalingTypeX = scalingTypeX;
    this->scalingTypeY = scalingTypeY;
}

/**
 *
 * @param the input vector to scale with
 * @return returns a vector a basis vector scaled by the input vector.
 *         With percentual value, it returns a multiple of the basis vector
 *         With decimal it simply returns the input vector
 */
glm::vec3 Vector2DScaler::GetScaledValues(glm::vec3 input)
{
    float calculatedX = input.x;
    float calculatedY = input.y;

    if(scalingTypeX == Percentual)
    {
        calculatedX = input.x * basis.x;
    }

    if(scalingTypeY == Percentual)
    {
        calculatedY = input.y * basis.y;
    }
    return {calculatedX, calculatedY, input.z};
}

GraphicsScaling Vector2DScaler::GetScalingTypeX() const
{
    return scalingTypeX;
}

void Vector2DScaler::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    this->scalingTypeX = scalingTypeX;
}

GraphicsScaling Vector2DScaler::GetScalingTypeY() const
{
    return scalingTypeY;
}

void Vector2DScaler::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    this->scalingTypeY = scalingTypeY;
}
