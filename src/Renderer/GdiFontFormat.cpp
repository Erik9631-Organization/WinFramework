//
// Created by Erik on 22/01/27.
//

#include "GdiFontFormat.h"

void GdiFontFormat::SetAlignment(int alignment)
{
    this->alignment = (Gdiplus::StringAlignment)alignment;
}

void GdiFontFormat::SetLineAlignment(int lineAlignment)
{
    this->lineAlignment = (Gdiplus::StringAlignment)lineAlignment;
}

int GdiFontFormat::GetAlingment() const
{
    return alignment;
}

int GdiFontFormat::GetLineAlingment() const
{
    return lineAlignment;
}
