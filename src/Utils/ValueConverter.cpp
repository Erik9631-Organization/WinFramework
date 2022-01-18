//
// Created by Erik on 1/18/2022.
//

#include "ValueConverter.h"

Gdiplus::PointF ValueConverter::PointToPointF(Gdiplus::Point point)
{
    return {(float)point.X, (float)point.Y};
}

Gdiplus::SizeF ValueConverter::SizeToSizeF(Gdiplus::Size size)
{
    return {(float)size.Width, (float)size.Height};
}
