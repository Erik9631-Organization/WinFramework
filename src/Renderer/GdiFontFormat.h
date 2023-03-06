//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDIFONTFORMAT_H
#define LII_GDIFONTFORMAT_H
#include "FontFormat.h"
#include <Windows.h>
#include <Gdiplus.h>



class GdiFontFormat
{
public:
    GdiFontFormat();
    GdiFontFormat(const FontFormat& fontFormat);

    void SetAlignment(int alignment);
    void SetLineAlignment(int lineAlignment);
    int GetAlignment() const;
    int GetLineAlignment() const;
private:
    Gdiplus::StringAlignment alignment;
    Gdiplus::StringAlignment lineAlignment;
};


#endif //LII_GDIFONTFORMAT_H
