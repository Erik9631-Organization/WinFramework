//
// Created by Erik on 22/01/26.
//

#ifndef LII_FONTFORMAT_H
#define LII_FONTFORMAT_H
#include <string>
#include "Vector2.h"

class FontFormat
{
public:
    virtual void SetAlignment(int alignment) = 0;
    virtual void SetLineAlignment(int lineAlignment) = 0;
    virtual int GetAlingment() const = 0;
    virtual int GetLineAlingment() const = 0;
};


#endif //LII_FONTFORMAT_H
