//
// Created by Erik on 1/12/2022.
//

#ifndef GRAPHICS_VECTOR2DSCALER_H
#define GRAPHICS_VECTOR2DSCALER_H
#include "Vector2.h"
#include "GraphicsScaling.h"

class Vector2DScaler
{
private:
    Vector2 parentVector;
    GraphicsScaling scalingTypeX;
    GraphicsScaling scalingTypeY;
public:
    Vector2DScaler(Vector2 parentVector, GraphicsScaling scalingTypeX, GraphicsScaling scalingTypeY);
    Vector2DScaler(Vector2 parentVector);

    GraphicsScaling GetScalingTypeX() const;

    void SetScalingTypeX(GraphicsScaling scalingTypeX);

    GraphicsScaling GetScalingTypeY() const;

    void SetScalingTypeY(GraphicsScaling scalingTypeY);
    Vector2 GetScaledValues(Vector2 input);


};


#endif //GRAPHICS_VECTOR2DSCALER_H
