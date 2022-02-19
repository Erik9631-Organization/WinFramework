//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERER_H
#define LII_OPENGLRENDERER_H
#include "Renderer.h"
class Renderable;

class OpenGLRenderer : public Renderer
{
private:
    //const Renderable& owner;
public:
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
    void SetColor(const Vector4 &color) override;
    void SetColor(const Vector3 &color) override;
    void SetThickness(float thickness) override;
    void SetFontFamily(std::wstring fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;

};


#endif //LII_OPENGLRENDERER_H
