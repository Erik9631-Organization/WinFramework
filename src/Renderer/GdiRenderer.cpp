//
// Created by Erik on 22/01/27.
//

#include "GdiRenderer.h"
#include "Vector4.h"
#include "Vector3.h"
#include <windows.h>
#include <gdiplus.h>
#include <CoreWindow.h>
#include "FontFormat.h"
#include "GdiFontFormat.h"
#include "CoreWindow.h"

using namespace Gdiplus;
unsigned int fpsfuckingcounter = 0;

void GdiRenderer::DrawEllipse(float x, float y, float width, float height)
{
    graphics.DrawEllipse(pen, x, y, width, height);
}

void GdiRenderer::DrawEllipse(float x, float y, Vector2 vector2)
{
    graphics.DrawEllipse(pen, x, y, vector2.GetY(), vector2.GetY());
}

void GdiRenderer::DrawLine(float x1, float y1, float x2, float y2)
{
    graphics.DrawLine(pen, x1, y1, x2, y2);
}

void GdiRenderer::DrawLine(Vector2 pos, Vector2 size)
{
    graphics.DrawLine(pen, pos.GetY(), pos.GetY(), size.GetX(), size.GetY());
}

void GdiRenderer::DrawRectangle(Vector2 pos, Vector2 size)
{
    graphics.DrawRectangle(pen, pos.GetX(), pos.GetY(), size.GetX(), size.GetY());
}

void GdiRenderer::DrawRectangle(float x, float y, float width, float height)
{
    graphics.DrawRectangle(pen, x, y, width, height);
}

void GdiRenderer::DrawString(const std::wstring &string, Vector2 position, const FontFormat &format, int len)
{
    StringFormat stringFormat{};
    stringFormat.SetAlignment((StringAlignment)format.GetAlingment());
    stringFormat.SetLineAlignment((StringAlignment)format.GetLineAlingment());

    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics.DrawString(string.c_str(), -1, font, {position.GetX(), position.GetY()}, &stringFormat, brush);
    fpsfuckingcounter++;
    delete font;
}

void GdiRenderer::FillEllipse(float x, float y, float width, float height)
{
    graphics.FillEllipse(brush, x, y, width, height);
}

void GdiRenderer::FillEllipse(Vector2 pos, Vector2 size)
{
    graphics.FillEllipse(brush, pos.GetX(), pos.GetY(), size.GetX(), size.GetY());
}

void GdiRenderer::FillRectangle(float x, float y, float width, float height)
{
    graphics.FillRectangle(brush, x, y, width, height);
}

void GdiRenderer::FillRectangle(Vector2 pos, Vector2 size)
{
    graphics.FillRectangle(brush, pos.GetX(), pos.GetY(), size.GetX(), size.GetY());
}

GdiRenderer::GdiRenderer(Gdiplus::Graphics &graphics) : graphics(graphics)
{
    pen = new Gdiplus::Pen(Gdiplus::Color::Black, 1.0f);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);
}

void GdiRenderer::SetColor(const Vector4 &color)
{
    BYTE a = (BYTE)color.GetW();
    BYTE r = (BYTE)color.GetX();
    BYTE g = (BYTE)color.GetY();
    BYTE b = (BYTE)color.GetZ();
    Color inputColor{a, r, g, b};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiRenderer::SetColor(const Vector3 &color)
{
    Color inputColor {(BYTE)color.GetX(), (BYTE)color.GetY(), (BYTE)color.GetZ()};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiRenderer::SetThickness(float thickness)
{
    pen->SetWidth(thickness);
}

void GdiRenderer::SetFontFamily(std::wstring fontFamily)
{
    delete this->fontFamily;
    this->fontFamily = new Gdiplus::FontFamily(L"Arial");
}

void GdiRenderer::SetFontSize(float fontSize)
{
    this->fontSize = fontSize;
}

std::unique_ptr<FontFormat> GdiRenderer::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

GdiRenderer::~GdiRenderer()
{
    delete pen;
    delete brush;
    delete fontFamily;
}

void GdiRenderer::Translate(Vector2 translation)
{
    graphics.TranslateTransform(translation.GetX(), translation.GetY());
}
