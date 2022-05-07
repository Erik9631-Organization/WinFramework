//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERER_H
#define LII_OPENGLRENDERER_H
#include "Renderer.h"
#include "glm.hpp"
#include "ModelBuilder.h"
#include "ResizeSubscriber.h"
#include "Model.h"
#include "Vector4.h"
#include "Vector2.h"
#include "DrawData2D.h"
#include "DefaultRenderingManager.h"

class RenderCommander;
class Window;

class OpenGLRenderer : public Renderer, ResizeSubscriber
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

    Vector2 lastShapeSize;
    Vector2 lastShapePos;

    std::unique_ptr<OpenGL::Model> lastShape;
    Window& window; //For the view matrix
    glm::mat4 defaultViewMatrix = glm::mat4{1.0f};
    glm::mat4* viewMatrix;
    OpenGL::ModelBuilder builder;
    Vector4 lastColor;
    Vector2 translation;
    OpenGL::RenderingManager& renderingManager;
private:
    void TransformModel(OpenGL::Model &model, const Vector2 &pos, const Vector2 &size);
public:
    OpenGLRenderer(Window &window, OpenGL::RenderingManager& manager);
    void DrawModel(const OpenGL::Model &model) override;
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
    void Translate(Vector2 translation) override;
    void CreateViewMatrix(float width, float height, glm::mat4& viewMatrix);
private:
    void OnResize(EventResizeInfo e) override;

};


#endif //LII_OPENGLRENDERER_H
