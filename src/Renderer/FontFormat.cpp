//
// Created by Erik on 22/01/26.
//

#include "FontFormat.h"

void FontFormat::SetAlignment(FontAlignment alignment)
{
    this->alignment = alignment;
}

void FontFormat::SetLineAlignment(FontAlignment lineAlignment)
{
    this->lineAlignment = lineAlignment;
}

FontAlignment FontFormat::GetAlignment() const
{
    return alignment;
}

FontAlignment FontFormat::GetLineAlignment() const
{
    return lineAlignment;
}
