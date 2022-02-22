//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERER_H
#define LII_OPENGLRENDERER_H
#include "Renderer.h"
#include "glm.hpp"
#include "Shape2DBuilder.h"
#include "ResizeSubscriber.h"
#include "Model.h"
#include "Vector4.h"
#include "Vector2.h"
#include "DrawData2D.h"

class Renderable;
class Window;

class OpenGLRenderer : public Renderer, ResizeSubscriber
{
private:
    enum class ShapeType
    {
        None,
        Rectangle,
    };
    ShapeType lastShapeType = ShapeType::None;
    DrawData2D lastDrawdata;

    Vector2 lastShapeSize;
    Vector2 lastShapePos;

    std::unique_ptr<Model> lastShape;
    Window& window; //For the view matrix
    std::shared_ptr<glm::mat4> viewMatrix;
    Shape2DBuilder builder;
    Vector4 lastColor;
    Vector2 translation;
public:
    OpenGLRenderer(Window& window);
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
private:
    void OnResize(EventResizeInfo e) override;

};


#endif //LII_OPENGLRENDERER_H
