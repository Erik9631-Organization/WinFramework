//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDISHAPERENDERER_H
#define LII_GDISHAPERENDERER_H
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
#include "ShapeRenderer.h"

class GdiShapeRenderer : public ShapeRenderer
{
public:
    std::unique_ptr<Gdiplus::Graphics> graphics;
    GdiShapeRenderer(std::unique_ptr<Gdiplus::Graphics> graphics);
    ~GdiShapeRenderer();
    void SetColor(const glm::ivec4 &color) override;
    void SetColor(const glm::ivec3 &color) override;
    void SetThickness(float thickness) override;
    void DrawEllipse(float x, float y, float width, float height) override;
    void DrawEllipse(float x, float y, glm::vec4 vector4) override;
    void DrawLine(float x1, float y1, float x2, float y2) override;
    void DrawLine(glm::vec4 pos, glm::vec4 size) override;
    void DrawRectangle(glm::vec3 pos, glm::vec3 size) override;
    void DrawRectangle(float x, float y, float width, float height) override;
    void DrawString(const std::wstring &string, glm::vec3 position, const FontFormat &format) override;
    void DrawFillEllipse(float x, float y, float width, float height) override;
    void DrawFillEllipse(glm::vec4 pos, glm::vec4 size) override;
    void DrawFillRectangle(float x, float y, float width, float height) override;
    void DrawFillRectangle(glm::vec3 pos, glm::vec3 size) override;
    void SetFontFamily(std::wstring fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(glm::vec3 translation) override;
    void DrawModel(const OpenGL::Model &model) override;

    void SetClippingRectangle(float x, float y, float width, float height) override;

    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

private:
    Gdiplus::Pen* pen = nullptr;
    Gdiplus::SolidBrush* brush = nullptr;
    Gdiplus::Font* font = nullptr;
    Gdiplus::FontFamily* fontFamily = nullptr;
    float fontSize = 12.0f;
};


#endif //LII_GDISHAPERENDERER_H
