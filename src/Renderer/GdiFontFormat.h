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
    GdiFontFormat();
    explicit GdiFontFormat(const FontFormat& fontFormat);

    void SetAlignment(int alignment) override;
    void SetLineAlignment(int lineAlignment) override;
    [[nodiscard]] int GetAlignment() const override;
    [[nodiscard]] int GetLineAlignment() const override;
private:
    Gdiplus::StringAlignment alignment;
    Gdiplus::StringAlignment lineAlignment;
};


#endif //LII_GDIFONTFORMAT_H
