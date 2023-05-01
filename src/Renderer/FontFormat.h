//
// Created by Erik on 22/01/26.
//

#ifndef LII_FONTFORMAT_H
#define LII_FONTFORMAT_H
#include <string>
#include "FontAlignment.h"

class FontFormat
{
public:
    virtual void SetAlignment(int alignment) = 0;
    virtual void SetLineAlignment(int lineAlignment) = 0;
    [[nodiscard]] virtual int GetAlignment() const = 0;
    [[nodiscard]] virtual int GetLineAlignment() const = 0;
    virtual ~FontFormat() = default;
};


#endif //LII_FONTFORMAT_H
