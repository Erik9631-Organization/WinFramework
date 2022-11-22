//
// Created by Erik on 1/18/2022.
//

#ifndef LII_VALUECONVERTER_H
#define LII_VALUECONVERTER_H
#include <Windows.h>
#include <gdiplus.h>

class ValueConverter
{
public:
    static Gdiplus::PointF PointToPointF(Gdiplus::Point point);
    static Gdiplus::SizeF SizeToSizeF(Gdiplus::Size size);
};


#endif //LII_VALUECONVERTER_H
