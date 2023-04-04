//
// Created by erik9 on 4/4/2023.
//

#ifndef LII_TEXTAPI_H
#define LII_TEXTAPI_H

//TODO rename TextApi to something that doesn't have Api

#include <string>
#include "Movable.h"
#include "FontAlignment.h"

class TextApi
{
public:
    virtual void SetFontSize(float fontSize) = 0;

    virtual void SetFontAlignment(FontAlignment alignment) = 0;

    virtual void SetFontLineAlignment(FontAlignment alignment) = 0;

    virtual void SetColor(const glm::ivec4 &color) = 0;

    virtual void SetText(const std::wstring& text) = 0;

    virtual void SetFontFamily(const std::wstring& fontFamily) = 0;

    virtual const glm::ivec4 &GetColor() = 0;

    virtual const std::wstring &GetText() = 0;

    virtual const std::wstring &GetFontFamily() = 0;

    virtual FontAlignment GetFontLineAlignment() = 0;

    virtual FontAlignment GetFontAlignment() = 0;
};
#endif //LII_TEXTAPI_H
