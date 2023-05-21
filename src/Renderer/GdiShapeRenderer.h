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
    void DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2) override;
    void DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;
    void DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format) override;
    void DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size) override;
    void DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;
    void SetFontFamily(const std::wstring &fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(glm::vec3 translation) override;
    void DrawModel(const OpenGL::Model &model) override;
    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size) override;

    void SetBufferRenderer(BufferRenderer &bufferRenderer) override;

private:
    Gdiplus::Pen* pen = nullptr;
    Gdiplus::SolidBrush* brush = nullptr;
    Gdiplus::Font* font = nullptr;
    Gdiplus::FontFamily* fontFamily = nullptr;
    float fontSize = 12.0f;
};


#endif //LII_GDISHAPERENDERER_H
