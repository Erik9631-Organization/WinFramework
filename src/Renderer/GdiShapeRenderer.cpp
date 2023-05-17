//
// Created by Erik on 22/01/27.
//

#include "GdiShapeRenderer.h"
#include <Windows.h>
#include <gdiplus.h>
#include "Core/Windows/WindowsCore.h"
#include "FontFormat.h"
#include "GdiFontFormat.h"
#include "Core/Windows/WindowsCore.h"

using namespace Gdiplus;

void GdiShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{
    graphics->DrawLine(pen, pos1.x, pos1.y, pos2.x, pos2.y);
}

void GdiShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    graphics->DrawRectangle(pen, pos.x, pos.y, size.x, size.y);
}

void GdiShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{
    StringFormat stringFormat{};
    stringFormat.SetAlignment((StringAlignment) format.GetAlignment());
    stringFormat.SetLineAlignment((StringAlignment) format.GetLineAlignment());

    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics->DrawString(string.c_str(), -1, font, {position.x, position.y}, &stringFormat, brush);
    delete font;
}


void GdiShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{
    graphics->FillEllipse(brush, pos.x, pos.y, size.x, size.y);
}

void GdiShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    graphics->FillRectangle(brush, pos.x, pos.y, size.x, size.y);
}

GdiShapeRenderer::GdiShapeRenderer(std::unique_ptr<Graphics> graphics)
{
    this->graphics = std::move(graphics);
    pen = new Gdiplus::Pen(Gdiplus::Color::Black, 1.0f);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);
}

void GdiShapeRenderer::SetColor(const glm::ivec4 &color)
{
    BYTE a = (BYTE)color.w;
    BYTE r = (BYTE)color.x;
    BYTE g = (BYTE)color.y;
    BYTE b = (BYTE)color.z;
    Color inputColor{a, r, g, b};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiShapeRenderer::SetColor(const glm::ivec3 &color)
{
    Color inputColor {(BYTE)color.x, (BYTE)color.y, (BYTE)color.z};
    brush->SetColor(inputColor);
    pen->SetColor(inputColor);
}

void GdiShapeRenderer::SetThickness(float thickness)
{
    pen->SetWidth(thickness);
}

void GdiShapeRenderer::SetFontFamily(const std::wstring &fontFamily)
{
    delete this->fontFamily;
    this->fontFamily = new Gdiplus::FontFamily(L"Arial");
}

void GdiShapeRenderer::SetFontSize(float fontSize)
{
    this->fontSize = fontSize;
}

std::unique_ptr<FontFormat> GdiShapeRenderer::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

GdiShapeRenderer::~GdiShapeRenderer()
{
    delete pen;
    delete brush;
    delete fontFamily;
}

void GdiShapeRenderer::Translate(glm::vec3 translation)
{
    graphics->TranslateTransform(translation.x, translation.y);
}

void GdiShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void GdiShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{
    graphics->SetClip(RectF(pos.x, pos.y, size.x, size.y), CombineModeReplace);
}

void GdiShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{
    graphics->DrawEllipse(pen, position.x, position.y, size.x, size.y);
}
