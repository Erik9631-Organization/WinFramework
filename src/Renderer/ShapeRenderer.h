//
// Created by Erik on 22/01/26.
//

#ifndef LII_SHAPERENDERER_H
#define LII_SHAPERENDERER_H

#include <string>
#include <memory>
#include <glm.hpp>
#include "Injectable.h"
#include "Buffer.h"

class FontFormat;
class RenderCommander;
class BufferRenderer;

namespace OpenGL
{
    class Model;
}

class ShapeRenderer : virtual public LiiInjector::Injectable
{
public:
    virtual void SetScreenBuffer(BufferRenderer &buffer) = 0;
    virtual void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size, bool drawFromCenter) = 0;
    //virtual void DrawImage(const Image& imageData, float x, float y);
    //virtual void DrawImage(const Image& imageData, vector2d viewPortSize);
    virtual void DrawModel(const OpenGL::Model &model) = 0;
    virtual void DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2) = 0;
    virtual void DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size) = 0;
    virtual void DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format) = 0;
    virtual void DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size, bool drawFromCenter = true) = 0;
    virtual void DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size) = 0;
    virtual void SetColor(const glm::ivec4 &color) = 0;
    virtual void SetColor(const glm::ivec3 &color) = 0;
    virtual void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) = 0;
    virtual void SetThickness(float thickness) = 0;
    virtual void SetFontFamily(const std::wstring &fontFamily) = 0;
    virtual void SetFontSize(float fontSize) = 0;
    virtual std::unique_ptr<FontFormat> CreateFontFormat() = 0;
    virtual void Translate(glm::vec3 translation) = 0;
    virtual ~ShapeRenderer() = default;
};


#endif //LII_SHAPERENDERER_H
