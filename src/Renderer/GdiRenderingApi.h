//
// Created by Erik on 22/01/27.
//

#ifndef LII_GDIRENDERINGAPI_H
#define LII_GDIRENDERINGAPI_H
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
#include "RenderingApi.h"

class GdiRenderingApi : public RenderingApi
{
public:
    std::unique_ptr<Gdiplus::Graphics> graphics;
    GdiRenderingApi(std::unique_ptr<Gdiplus::Graphics> graphics);
    ~GdiRenderingApi();
    void SetColor(const Vector4& color) override;
    void SetColor(const Vector3& color) override;
    void SetThickness(float thickness) override;
    void DrawEllipse(float x, float y, float width, float height) override;
    void DrawEllipse(float x, float y, glm::vec2 vector2) override;
    void DrawLine(float x1, float y1, float x2, float y2) override;
    void DrawLine(glm::vec2 pos, glm::vec2 size) override;
    void DrawRectangle(glm::vec2 pos, glm::vec2 size) override;
    void DrawRectangle(float x, float y, float width, float height) override;
    void DrawString(const std::wstring &string, glm::vec2 position, const FontFormat &format, int len) override;
    void DrawFillEllipse(float x, float y, float width, float height) override;
    void DrawFillEllipse(glm::vec2 pos, glm::vec2 size) override;
    void DrawFillRectangle(float x, float y, float width, float height) override;
    void DrawFillRectangle(glm::vec2 pos, glm::vec2 size) override;
    void SetFontFamily(std::wstring fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(glm::vec2 translation) override;
    void DrawModel(const OpenGL::Model &model) override;

    void SetClippingRectangle(float x, float y, float width, float height) override;

    void SetClippingRectangle(glm::vec2 pos, glm::vec2 size) override;

private:
    Gdiplus::Pen* pen = nullptr;
    Gdiplus::SolidBrush* brush = nullptr;
    Gdiplus::Font* font = nullptr;
    Gdiplus::FontFamily* fontFamily = nullptr;
    float fontSize = 12.0f;
};


#endif //LII_GDIRENDERINGAPI_H
