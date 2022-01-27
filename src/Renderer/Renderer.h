//
// Created by Erik on 22/01/26.
//

#ifndef LII_RENDERER_H
#define LII_RENDERER_H
class Vector2;
#include <string>
class FontFormat;

class Renderer
{
    virtual void DrawEllipse(float x,float y, float width, float height) = 0;
    virtual void DrawEllipse(float x,float y, Vector2) = 0;
    //virtual void DrawImage(const Image& imageData, float x, float y);
    //virtual void DrawImage(const Image& imageData, vector2d position);
    virtual void DrawLine(float x1,float y1, float x2, float y2) = 0;
    virtual void DrawLine(Vector2 pos, Vector2 size) = 0;
    virtual void DrawRectangle(Vector2 pos, Vector2 size) = 0;
    virtual void DrawRectangle(float x, float y, float width, float height) = 0;
    virtual void DrawString(const std::wstring& string, const FontFormat& format) = 0;
    virtual void FillEllipse(float x, float y, float width, float height) = 0;
    virtual void FillEllipse(Vector2 pos, Vector2 size) = 0;
    virtual void FillRectangle(float x, float y, float width, float height) = 0;
    virtual void FillRectangle(Vector2 pos, Vector2 size) = 0;
};


#endif //LII_RENDERER_H
