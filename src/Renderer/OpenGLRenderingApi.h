//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERINGAPI_H
#define LII_OPENGLRENDERINGAPI_H
#include "RenderingApi.h"
#include "glm.hpp"
#include "ModelBuilder.h"
#include "ResizeSubscriber.h"
#include "Model.h"
#include "DrawData2D.h"
#include "DefaultRenderingManager.h"

class RenderCommander;
class Window;

class OpenGLRenderingApi : public RenderingApi, ResizeSubscriber
{
private:
    enum class ShapeType
    {
        None,
        FillRectangle,
        Rectangle,
        FillEllipse,
        Ellipse
    };
    ShapeType lastShapeType = ShapeType::None;
    DrawData2D originalData;

    glm::vec2 lastShapeSize;
    glm::vec2 lastShapePos;

    std::unique_ptr<OpenGL::Model> lastShape;
    Window& window; //For the view matrix
    glm::mat4 defaultViewMatrix = glm::mat4{1.0f};
    glm::mat4* viewMatrix;
    OpenGL::ModelBuilder builder;
    glm::vec4 lastColor;
    glm::vec2 translation;
    OpenGL::RenderingManager& renderingManager;
private:
    void TransformModel(OpenGL::Model &model, const glm::vec2 &pos, const glm::vec2 &size);
public:
    OpenGLRenderingApi(Window &window, OpenGL::RenderingManager& manager);
    void DrawModel(const OpenGL::Model &model) override;
    void DrawEllipse(float x, float y, float width, float height) override;
    void DrawEllipse(float x, float y, glm::vec4 vector4) override;
    void DrawLine(float x1, float y1, float x2, float y2) override;
    void DrawLine(glm::vec4 pos, glm::vec4 size) override;
    void DrawRectangle(glm::vec4 pos, glm::vec4 size) override;
    void DrawRectangle(float x, float y, float width, float height) override;
    void DrawString(const std::wstring &string, glm::vec4 position, const FontFormat &format, int len) override;
    void DrawFillEllipse(float x, float y, float width, float height) override;
    void DrawFillEllipse(glm::vec4 pos, glm::vec4 size) override;
    void DrawFillRectangle(float x, float y, float width, float height) override;
    void DrawFillRectangle(glm::vec4 pos, glm::vec4 size) override;
    void SetColor(const glm::vec4 &color) override;
    void SetColor(const glm::vec3 &color) override;
    void SetThickness(float thickness) override;
    void SetFontFamily(std::wstring fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(glm::vec4 translation) override;
    void CreateViewMatrix(float width, float height, glm::mat4& viewMatrix);

    void SetClippingRectangle(float x, float y, float width, float height) override;

    void SetClippingRectangle(glm::vec4 pos, glm::vec4 size) override;

private:
    void OnResize(EventResizeInfo e) override;

};


#endif //LII_OPENGLRENDERINGAPI_H
