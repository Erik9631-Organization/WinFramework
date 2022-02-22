//
// Created by Erik on 22/01/26.
//

#ifndef LII_RENDERER_H
#define LII_RENDERER_H
class Vector2;
#include <string>
#include <memory>
class FontFormat;
class Vector4;
class Vector3;
class Renderable;

class Renderer
{
public:
    virtual void DrawEllipse(float x,float y, float width, float height) = 0;
    virtual void DrawEllipse(float x,float y, Vector2) = 0;
    //virtual void DrawImage(const Image& imageData, float x, float y);
    //virtual void DrawImage(const Image& imageData, vector2d position);
    virtual void DrawLine(float x1,float y1, float x2, float y2) = 0;
    virtual void DrawLine(Vector2 pos, Vector2 size) = 0;
    virtual void DrawRectangle(Vector2 pos, Vector2 size) = 0;
    virtual void DrawRectangle(float x, float y, float width, float height) = 0;
    virtual void DrawString(const std::wstring &string, Vector2 position, const FontFormat &format, int len) = 0;
    virtual void FillEllipse(float x, float y, float width, float height) = 0;
    virtual void FillEllipse(Vector2 pos, Vector2 size) = 0;
    virtual void FillRectangle(float x, float y, float width, float height) = 0;
    virtual void FillRectangle(Vector2 pos, Vector2 size) = 0;
    virtual void SetColor(const Vector4 &color) = 0;
    virtual void SetColor(const Vector3 &color) = 0;
    virtual void SetThickness(float thickness) = 0;
    virtual void SetFontFamily(std::wstring fontFamily) = 0;
    virtual void SetFontSize(float fontSize) = 0;
    virtual std::unique_ptr<FontFormat> CreateFontFormat() = 0;
    virtual void Translate(Vector2 translation) = 0;
};


#endif //LII_RENDERER_H
