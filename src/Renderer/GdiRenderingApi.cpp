//
// Created by Erik on 22/01/27.
//

#include "GdiRenderingApi.h"
#include <Windows.h>
#include <gdiplus.h>
#include "Core/Windows/WindowsCore.h"
#include "FontFormat.h"
#include "GdiFontFormat.h"
#include "Core/Windows/WindowsCore.h"

using namespace Gdiplus;

void GdiRenderingApi::DrawEllipse(float x, float y, float width, float height)
{
    graphics->DrawEllipse(pen, x, y, width, height);
}

void GdiRenderingApi::DrawEllipse(float x, float y, glm::vec4 vector4)
{
    graphics->DrawEllipse(pen, x, y, vector4.x, vector4.y);
}

void GdiRenderingApi::DrawLine(float x1, float y1, float x2, float y2)
{
    graphics->DrawLine(pen, x1, y1, x2, y2);
}

void GdiRenderingApi::DrawLine(glm::vec4 pos, glm::vec4 size)
{
    graphics->DrawLine(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawRectangle(glm::vec3 pos, glm::vec3 size)
{
    graphics->DrawRectangle(pen, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawRectangle(float x, float y, float width, float height)
{
    graphics->DrawRectangle(pen, x, y, width, height);
}

void GdiRenderingApi::DrawString(const std::wstring &string, glm::vec3 position, const FontFormat &format)
{
    StringFormat stringFormat{};
    stringFormat.SetAlignment((StringAlignment) format.GetAlignment());
    stringFormat.SetLineAlignment((StringAlignment) format.GetLineAlignment());

    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics->DrawString(string.c_str(), -1, font, {position.x, position.y}, &stringFormat, brush);
    delete font;
}

void GdiRenderingApi::DrawFillEllipse(float x, float y, float width, float height)
{
    graphics->FillEllipse(brush, x, y, width, height);
}

void GdiRenderingApi::DrawFillEllipse(glm::vec4 pos, glm::vec4 size)
{
    graphics->FillEllipse(brush, pos.x, pos.y, size.x, size.y);
}

void GdiRenderingApi::DrawFillRectangle(float x, float y, float width, float height)
{
    graphics->FillRectangle(brush, x, y, width, height);
}

void GdiRenderingApi::DrawFillRectangle(glm::vec3 pos, glm::vec3 size)
{
    graphics->FillRectangle(brush, pos.x, pos.y, size.x, size.y);
}

GdiRenderingApi::GdiRenderingApi(std::unique_ptr<Graphics> graphics)
{
    this->graphics = std::move(graphics);
    pen = new Gdiplus::Pen(Gdiplus::Color::Black, 1.0f);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);
}

void GdiRenderingApi::SetColor(const glm::ivec4 &color)
{
    BYTE a = (BYTE)color.w;
    BYTE r = (BYTE)color.x;
    BYTE g = (BYTE)color.y;
    BYTE b = (BYTE)color.z;
    Color inputColor{a, r, g, b};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiRenderingApi::SetColor(const glm::ivec3 &color)
{
    Color inputColor {(BYTE)color.x, (BYTE)color.y, (BYTE)color.z};
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

void GdiRenderingApi::Translate(glm::vec3 translation)
{
    graphics->TranslateTransform(translation.x, translation.y);
}

void GdiRenderingApi::DrawModel(const OpenGL::Model &model)
{

}

void GdiRenderingApi::SetClippingRectangle(float x, float y, float width, float height)
{
    graphics->SetClip(RectF(x, y, width, height), CombineModeReplace);
}

void GdiRenderingApi::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{
    SetClippingRectangle(pos.x, pos.y, size.x, size.y);
}
