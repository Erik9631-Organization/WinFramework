//
// Created by Erik on 22/01/26.
//

#ifndef LII_FONTFORMAT_H
#define LII_FONTFORMAT_H
#include <string>
#include "FontAlignment.h"

class FontFormat
{
    FontAlignment alignment = FontAlignment::FontAlignmentNear;
    FontAlignment lineAlignment =  FontAlignment::FontAlignmentNear;
public:
    void SetAlignment(FontAlignment alignment);
    void SetLineAlignment(FontAlignment lineAlignment);
    [[nodiscard]] FontAlignment GetAlignment() const;
    [[nodiscard]] FontAlignment GetLineAlignment() const;
};


#endif //LII_FONTFORMAT_H
