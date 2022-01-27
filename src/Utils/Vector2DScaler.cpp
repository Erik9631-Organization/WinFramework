//
// Created by Erik on 1/12/2022.
//

#include "Vector2DScaler.h"

Vector2DScaler::Vector2DScaler(Vector2 parentVector) : Vector2DScaler(parentVector, Decimal, Decimal)
{

}


Vector2DScaler::Vector2DScaler(Vector2 parentVector, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY)
{
    this->scalingTypeX = scalingTypeX;
    this->scalingTypeY = scalingTypeY;
    this->parentVector = parentVector;
}


Vector2 Vector2DScaler::GetScaledValues(Vector2 input)
{
    float calculatedX = input.GetX();
    float calculatedY = input.GetY();

    if(scalingTypeX == Percentual)
    {
        calculatedX = input.GetX() * parentVector.GetX();
    }

    if(scalingTypeY == Percentual)
    {
        calculatedY = input.GetY() * parentVector.GetY();
    }
    return {calculatedX, calculatedY};
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
