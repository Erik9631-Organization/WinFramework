//
// Created by Erik on 22/01/26.
//

#ifndef LII_RENDERINGAPI_H
#define LII_RENDERINGAPI_H

#include <string>
#include <memory>
#include <glm.hpp>

class FontFormat;
class Vector4;
class Vector3;
class RenderCommander;

namespace OpenGL
{
    class Model;
}

class RenderingApi
{
public:
    virtual void DrawEllipse(float x,float y, float width, float height) = 0;
    virtual void DrawEllipse(float x, float y, glm::vec2) = 0;
    //virtual void DrawImage(const Image& imageData, float x, float y);
    //virtual void DrawImage(const Image& imageData, vector2d position);
    virtual void DrawModel(const OpenGL::Model &model) = 0;
    virtual void DrawLine(float x1,float y1, float x2, float y2) = 0;
    virtual void DrawLine(glm::vec2 pos, glm::vec2 size) = 0;
    virtual void DrawRectangle(glm::vec2 pos, glm::vec2 size) = 0;
    virtual void DrawRectangle(float x, float y, float width, float height) = 0;
    virtual void DrawString(const std::wstring &string, glm::vec2 position, const FontFormat &format, int len) = 0;
    virtual void DrawFillEllipse(float x, float y, float width, float height) = 0;
    virtual void DrawFillEllipse(glm::vec2 pos, glm::vec2 size) = 0;
    virtual void DrawFillRectangle(float x, float y, float width, float height) = 0;
    virtual void DrawFillRectangle(glm::vec2 pos, glm::vec2 size) = 0;
    virtual void SetColor(const Vector4 &color) = 0;
    virtual void SetColor(const Vector3 &color) = 0;
    virtual void SetClippingRectangle(float x, float y, float width, float height) = 0;
    virtual void SetClippingRectangle(glm::vec2 pos, glm::vec2 size) = 0;
    virtual void SetThickness(float thickness) = 0;
    virtual void SetFontFamily(std::wstring fontFamily) = 0;
    virtual void SetFontSize(float fontSize) = 0;
    virtual std::unique_ptr<FontFormat> CreateFontFormat() = 0;
    virtual void Translate(glm::vec2 translation) = 0;
    virtual ~RenderingApi() = default;
};


#endif //LII_RENDERINGAPI_H
