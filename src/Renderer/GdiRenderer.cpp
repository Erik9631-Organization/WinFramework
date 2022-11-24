//
// Created by Erik on 22/01/27.
//

#include "GdiRenderer.h"
#include "Vector4.h"
#include "Vector3.h"
#include <Windows.h>
#include <gdiplus.h>
#include "Core/Windows/WindowsCore.h"
#include "FontFormat.h"
#include "GdiFontFormat.h"
#include "Core/Windows/WindowsCore.h"

using namespace Gdiplus;
unsigned int fpsfuckingcounter = 0;

void GdiRenderer::DrawEllipse(float x, float y, float width, float height)
{
    graphics.DrawEllipse(pen, x, y, width, height);
}

void GdiRenderer::DrawEllipse(float x, float y, glm::vec2 vector2)
{
    graphics.DrawEllipse(pen, x, y, vector2.x, vector2.y);
}

void GdiRenderer::DrawLine(float x1, float y1, float x2, float y2)
{
    graphics.DrawLine(pen, x1, y1, x2, y2);
}

void GdiRenderer::DrawLine(glm::vec2 pos, glm::vec2 size)
{
    graphics.DrawLine(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderer::DrawRectangle(glm::vec2 pos, glm::vec2 size)
{
    graphics.DrawRectangle(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderer::DrawRectangle(float x, float y, float width, float height)
{
    graphics.DrawRectangle(pen, x, y, width, height);
}

void GdiRenderer::DrawString(const std::wstring &string, glm::vec2 position, const FontFormat &format, int len)
{
    StringFormat stringFormat{};
    stringFormat.SetAlignment((StringAlignment)format.GetAlingment());
    stringFormat.SetLineAlignment((StringAlignment)format.GetLineAlingment());

    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics.DrawString(string.c_str(), -1, font, {position.x, position.y}, &stringFormat, brush);
    fpsfuckingcounter++;
    delete font;
}

void GdiRenderer::FillEllipse(float x, float y, float width, float height)
{
    graphics.FillEllipse(brush, x, y, width, height);
}

void GdiRenderer::FillEllipse(glm::vec2 pos, glm::vec2 size)
{
    graphics.FillEllipse(brush, pos.x, pos.y, size.x, size.y);
}

void GdiRenderer::FillRectangle(float x, float y, float width, float height)
{
    graphics.FillRectangle(brush, x, y, width, height);
}

void GdiRenderer::FillRectangle(glm::vec2 pos, glm::vec2 size)
{
    graphics.FillRectangle(brush, pos.x, pos.y, size.x, size.y);
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

void GdiRenderer::Translate(glm::vec2 translation)
{
    graphics.TranslateTransform(translation.x, translation.y);
}

void GdiRenderer::DrawModel(const OpenGL::Model &model)
{

}
