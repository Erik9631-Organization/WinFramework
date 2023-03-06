//
// Created by Erik on 22/01/27.
//

#include "GdiFontFormat.h"
using namespace Gdiplus;

void GdiFontFormat::SetAlignment(int alignment)
{
    this->alignment = (Gdiplus::StringAlignment)alignment;
}

void GdiFontFormat::SetLineAlignment(int lineAlignment)
{
    this->lineAlignment = (Gdiplus::StringAlignment)lineAlignment;
}

int GdiFontFormat::GetAlignment() const
{
    return alignment;
}

int GdiFontFormat::GetLineAlignment() const
{
    return lineAlignment;
}

GdiFontFormat::GdiFontFormat()
{
    this->alignment = StringAlignment::StringAlignmentNear;
    this->lineAlignment = StringAlignment::StringAlignmentNear;
}

GdiFontFormat::GdiFontFormat(const FontFormat &fontFormat)
{
    this->alignment = static_cast<Gdiplus::StringAlignment>(fontFormat.GetAlignment());
    this->lineAlignment = static_cast<Gdiplus::StringAlignment>(fontFormat.GetLineAlignment());
}
