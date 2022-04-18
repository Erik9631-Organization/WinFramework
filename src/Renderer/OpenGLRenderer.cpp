//
// Created by Erik on 01/02/22.
//

#include "OpenGLRenderer.h"
#include "Vector2.h"
#include <memory>
#include "FontFormat.h"
#include "Model.h"
#include "Window.h"
#include "EventResizeInfo.h"
#include "ShaderProgram.h"
#include "UniformProperties.h"
#include "GdiFontFormat.h"
#include "CoreWindow.h"

void OpenGLRenderer::DrawEllipse(float x, float y, float width, float height)
{

}

void OpenGLRenderer::DrawEllipse(float x, float y, Vector2 vector2)
{

}

void OpenGLRenderer::DrawLine(float x1, float y1, float x2, float y2)
{

}

void OpenGLRenderer::DrawLine(Vector2 pos, Vector2 size)
{

}

void OpenGLRenderer::DrawRectangle(Vector2 pos, Vector2 size)
{
    if(lastShapeType != ShapeType::Rectangle)
    {
        lastShape = builder.CreateRectangle(pos.GetX() + translation.GetX(), pos.GetY() + translation.GetX(),
                                                size.GetX(), size.GetY());
        originalData = {pos, size};
        lastShapeType = ShapeType::Rectangle;
    }
    else
        TransformModel(*lastShape, pos, size);
    lastShape->GetShader().GetUniformProperties().SetProperty("color", lastColor.GetX(), lastColor.GetY(), lastColor.GetZ(), 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLRenderer::DrawRectangle(float x, float y, float width, float height)
{
    DrawRectangle({x, y}, {width, height});
}

void OpenGLRenderer::DrawString(const std::wstring &string, Vector2 position, const FontFormat &format, int len)
{

}

void OpenGLRenderer::FillEllipse(float x, float y, float width, float height)
{

}

void OpenGLRenderer::FillEllipse(Vector2 pos, Vector2 size)
{

}

void OpenGLRenderer::FillRectangle(float x, float y, float width, float height)
{
    //FillRectangle({x, y}, {width, height});
}

void OpenGLRenderer::FillRectangle(Vector2 pos, Vector2 size)
{
    if(lastShapeType != ShapeType::FillRectangle)
    {
        lastShape = builder.CreateFillRectangle(pos.GetX() + translation.GetX(), pos.GetY() + translation.GetX(),
                                                size.GetX(), size.GetY());
        originalData = {pos, size};
        lastShapeType = ShapeType::FillRectangle;
    }
    else
        TransformModel(*lastShape, pos, size);

    lastShape->GetShader().GetUniformProperties().SetProperty( "color",lastColor.GetX(), lastColor.GetY(), lastColor.GetZ(), 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLRenderer::SetColor(const Vector4 &color)
{
    lastColor = {color.GetX()/255, color.GetY()/255, color.GetZ()/255, color.GetW()/255};
}

void OpenGLRenderer::SetColor(const Vector3 &color)
{
    lastColor = {color.GetX()/255, color.GetY()/255, color.GetZ()/255, 1.0f};

}

void OpenGLRenderer::SetThickness(float thickness)
{

}

void OpenGLRenderer::SetFontFamily(std::wstring fontFamily)
{

}

void OpenGLRenderer::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> OpenGLRenderer::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

OpenGLRenderer::OpenGLRenderer(Window &window, OpenGL::RenderingManager& manager) : window(window), renderingManager(manager)
{
    window.AddOnResizeSubscriber(*this);
    viewMatrix = &defaultViewMatrix;
    CreateViewMatrix(window.GetWidth(), window.GetHeight(), *viewMatrix);
    builder.SetProjectionMatrix(viewMatrix);
}

void OpenGLRenderer::OnResize(EventResizeInfo e)
{
    CreateViewMatrix(e.GetSize().GetX(), e.GetSize().GetY(), *viewMatrix);
}

void OpenGLRenderer::Translate(Vector2 translation)
{
    this->translation = translation;
}

void OpenGLRenderer::CreateViewMatrix(float width, float height, glm::mat4 &viewMatrix)
{
    viewMatrix =
        {
        2.0f/width, 0, 0, -1,
        0, -2.0f/height, 0, 1,
        0, 0, 1, 0,
        0, 0, 0, 1
        };
    viewMatrix = glm::transpose(viewMatrix);
}

void OpenGLRenderer::TransformModel(OpenGL::Model &model, const Vector2 &pos, const Vector2 &size)
{
    float sizeXDelta = size.GetX() / originalData.GetSize().GetX();
    float sizeYDelta = size.GetY() / originalData.GetSize().GetY();

    model.ResetTransform();
    model.Scale({sizeXDelta, sizeYDelta, 1.0f});
    model.Translate({translation.GetX(), translation.GetY(), 0.0f});
    model.Translate({pos.GetX(), pos.GetY(), 0.0f});
}

void OpenGLRenderer::DrawModel(const OpenGL::Model &model)
{
    if(!renderingManager.HasModel(model))
        renderingManager.AddModel(model);

    renderingManager.Move(model);
}
