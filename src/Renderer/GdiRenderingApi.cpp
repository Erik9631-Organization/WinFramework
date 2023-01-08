//
// Created by Erik on 22/01/27.
//

#include "GdiRenderingApi.h"
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

void GdiRenderingApi::DrawEllipse(float x, float y, float width, float height)
{
    graphics->DrawEllipse(pen, x, y, width, height);
}

void GdiRenderingApi::DrawEllipse(float x, float y, glm::vec2 vector2)
{
    graphics->DrawEllipse(pen, x, y, vector2.x, vector2.y);
}

void GdiRenderingApi::DrawLine(float x1, float y1, float x2, float y2)
{
    graphics->DrawLine(pen, x1, y1, x2, y2);
}

void GdiRenderingApi::DrawLine(glm::vec2 pos, glm::vec2 size)
{
    graphics->DrawLine(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawRectangle(glm::vec2 pos, glm::vec2 size)
{
    graphics->DrawRectangle(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawRectangle(float x, float y, float width, float height)
{
    graphics->DrawRectangle(pen, x, y, width, height);
}

void GdiRenderingApi::DrawString(const std::wstring &string, glm::vec2 position, const FontFormat &format, int len)
{
    StringFormat stringFormat{};
    stringFormat.SetAlignment((StringAlignment)format.GetAlingment());
    stringFormat.SetLineAlignment((StringAlignment)format.GetLineAlingment());

    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics->DrawString(string.c_str(), -1, font, {position.x, position.y}, &stringFormat, brush);
    fpsfuckingcounter++;
    delete font;
}

void GdiRenderingApi::DrawFillEllipse(float x, float y, float width, float height)
{
    graphics->FillEllipse(brush, x, y, width, height);
}

void GdiRenderingApi::DrawFillEllipse(glm::vec2 pos, glm::vec2 size)
{
    graphics->FillEllipse(brush, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawFillRectangle(float x, float y, float width, float height)
{
    graphics->FillRectangle(brush, x, y, width, height);
}

void GdiRenderingApi::DrawFillRectangle(glm::vec2 pos, glm::vec2 size)
{
    graphics->FillRectangle(brush, pos.x, pos.y, size.x, size.y);
}

GdiRenderingApi::GdiRenderingApi(std::unique_ptr<Graphics> graphics)
{
    this->graphics = std::move(graphics);
    pen = new Gdiplus::Pen(Gdiplus::Color::Black, 1.0f);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);
}

void GdiRenderingApi::SetColor(const Vector4 &color)
{
    BYTE a = (BYTE)color.GetW();
    BYTE r = (BYTE)color.GetX();
    BYTE g = (BYTE)color.GetY();
    BYTE b = (BYTE)color.GetZ();
    Color inputColor{a, r, g, b};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiRenderingApi::SetColor(const Vector3 &color)
{
    Color inputColor {(BYTE)color.GetX(), (BYTE)color.GetY(), (BYTE)color.GetZ()};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiRenderingApi::SetThickness(float thickness)
{
    pen->SetWidth(thickness);
}

void GdiRenderingApi::SetFontFamily(std::wstring fontFamily)
{
    delete this->fontFamily;
    this->fontFamily = new Gdiplus::FontFamily(L"Arial");
}

void GdiRenderingApi::SetFontSize(float fontSize)
{
    this->fontSize = fontSize;
}

std::unique_ptr<FontFormat> GdiRenderingApi::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

GdiRenderingApi::~GdiRenderingApi()
{
    delete pen;
    delete brush;
    delete fontFamily;
}

void GdiRenderingApi::Translate(glm::vec2 translation)
{
    graphics->TranslateTransform(translation.x, translation.y);
}

void GdiRenderingApi::DrawModel(const OpenGL::Model &model)
{

}
