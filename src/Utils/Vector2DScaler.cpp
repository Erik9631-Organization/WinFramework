//
// Created by Erik on 1/12/2022.
//

#include "Vector2DScaler.h"

Vector2DScaler::Vector2DScaler(glm::vec4 parentVector) : Vector2DScaler(parentVector, Decimal, Decimal)
{

}


Vector2DScaler::Vector2DScaler(glm::vec4 parentVector, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY)
{
    this->scalingTypeX = scalingTypeX;
    this->scalingTypeY = scalingTypeY;
    this->parentVector = parentVector;
}


glm::vec4 Vector2DScaler::GetScaledValues(glm::vec4 input)
{
    float calculatedX = input.x;
    float calculatedY = input.y;

    if(scalingTypeX == Percentual)
    {
        calculatedX = input.x * parentVector.x;
    }

    if(scalingTypeY == Percentual)
    {
        calculatedY = input.y * parentVector.y;
    }
    return {calculatedX, calculatedY, 0, 0};
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
