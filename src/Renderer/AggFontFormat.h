//
// Created by erik9 on 5/22/2023.
//

#ifndef LII_AGGFONTFORMAT_H
#define LII_AGGFONTFORMAT_H
#include "FontFormat.h"

class AggFontFormat : public FontFormat
{
public:
    void SetAlignment(int alignment) override;

    void SetLineAlignment(int lineAlignment) override;

    int GetAlignment() const override;

    int GetLineAlignment() const override;

};


#endif //LII_AGGFONTFORMAT_H
