//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDIFONTFORMAT_H
#define LII_GDIFONTFORMAT_H
#include "FontFormat.h"
#include <Windows.h>
#include <Gdiplus.h>



class GdiFontFormat : public FontFormat
{
public:
    void SetAlignment(int alignment) override;
    void SetLineAlignment(int lineAlignment) override;
    int GetAlingment() const override;
    int GetLineAlingment() const override;
private:
    Gdiplus::StringAlignment alignment;
    Gdiplus::StringAlignment lineAlignment;
};


#endif //LII_GDIFONTFORMAT_H
