//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDIRENDERER_H
#define LII_GDIRENDERER_H
namespace Gdiplus
{
    class Graphics;
    class Pen;
    class SolidBrush;
    class Font;
    class FontFamily;
    class Color;
}
class Vector3;
class Vector4;

#include "Renderer.h"
#include "Vector2.h"

class GdiRenderer : public Renderer
{
public:
    Gdiplus::Graphics& graphics;
    GdiRenderer(Gdiplus::Graphics& graphics);
    ~GdiRenderer();
    void SetColor(const Vector4& color) override;
    void SetColor(const Vector3& color) override;
    void SetThickness(float thickness) override;
    void DrawEllipse(float x, float y, float width, float height) override;
    void DrawEllipse(float x, float y, Vector2 vector2) override;
    void DrawLine(float x1, float y1, float x2, float y2) override;
    void DrawLine(Vector2 pos, Vector2 size) override;
    void DrawRectangle(Vector2 pos, Vector2 size) override;
    void DrawRectangle(float x, float y, float width, float height) override;
    void DrawString(const std::wstring &string, Vector2 position, const FontFormat &format, int len) override;
    void FillEllipse(float x, float y, float width, float height) override;
    void FillEllipse(Vector2 pos, Vector2 size) override;
    void FillRectangle(float x, float y, float width, float height) override;
    void FillRectangle(Vector2 pos, Vector2 size) override;
    void SetFontFamily(std::wstring fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(Vector2 translation) override;
    void DrawModel(const OpenGL::Model &model) override;
private:
    Gdiplus::Pen* pen = nullptr;
    Gdiplus::SolidBrush* brush = nullptr;
    Gdiplus::Font* font = nullptr;
    Gdiplus::FontFamily* fontFamily = nullptr;
    float fontSize = 12.0f;
};


#endif //LII_GDIRENDERER_H
