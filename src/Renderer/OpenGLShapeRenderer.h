//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLSHAPERENDERER_H
#define LII_OPENGLSHAPERENDERER_H
#include "ShapeRenderer.h"
#include "glm.hpp"
#include "ModelBuilder.h"
#include "ResizeSubscriber.h"
#include "Model.h"
#include "DrawData2D.h"
#include "DefaultRenderingManager.h"

class RenderCommander;
class Window;

class OpenGLShapeRenderer : public ShapeRenderer, public ResizeSubscriber
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
    OpenGLShapeRenderer(Window &window, OpenGL::RenderingManager& manager);
    void DrawModel(const OpenGL::Model &model) override;
    void DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2) override;
    void DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;
    void DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format) override;
    void DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size) override;
    void DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;
    void SetColor(const glm::ivec4 &color) override;
    void SetColor(const glm::ivec3 &color) override;
    void SetThickness(float thickness) override;
    void SetFontFamily(const std::wstring &fontFamily) override;
    void SetFontSize(float fontSize) override;
    std::unique_ptr<FontFormat> CreateFontFormat() override;
    void Translate(glm::vec3 translation) override;
    void CreateViewMatrix(float width, float height, glm::mat4& viewMatrix);
    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size) override;

private:
    void OnResize(EventResizeInfo e) override;

};


#endif //LII_OPENGLSHAPERENDERER_H
