//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDIRENDERER_H
#define LII_GDIRENDERER_H
namespace Gdiplus
{
    class Graphics;
    class Pen;
    class Brush;
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
    void SetColor(const Vector4& color);
    void SetColor(const Vector3& color);
    void SetThickness(float thickness);
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
private:
    Gdiplus::Pen* pen;
    Gdiplus::SolidBrush* brush;
    Gdiplus::Font* font;
};


#endif //LII_GDIRENDERER_H
