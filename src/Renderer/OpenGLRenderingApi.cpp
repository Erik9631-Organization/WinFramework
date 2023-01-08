//
// Created by Erik on 01/02/22.
//

#include "OpenGLRenderingApi.h"
#include <memory>
#include "FontFormat.h"
#include "Model.h"
#include "Window.h"
#include "EventResizeInfo.h"
#include "ShaderProgram.h"
#include "UniformProperties.h"
#include "GdiFontFormat.h"
#include "Core/Windows/WindowsCore.h"

void OpenGLRenderingApi::DrawEllipse(float x, float y, float width, float height)
{

}

void OpenGLRenderingApi::DrawEllipse(float x, float y, glm::vec2 vector2)
{

}

void OpenGLRenderingApi::DrawLine(float x1, float y1, float x2, float y2)
{

}

void OpenGLRenderingApi::DrawLine(glm::vec2 pos, glm::vec2 size)
{

}

void OpenGLRenderingApi::DrawRectangle(glm::vec2 pos, glm::vec2 size)
{
    if(lastShapeType != ShapeType::Rectangle)
    {
        lastShape = builder.CreateRectangle(pos.x + translation.x, pos.y + translation.y,
                                                size.x, size.y);
        originalData = {pos, size};
        lastShapeType = ShapeType::Rectangle;
    }
    else
        TransformModel(*lastShape, pos, size);
    lastShape->GetShaderProgram().GetUniformProperties().SetProperty("color", lastColor.GetX(), lastColor.GetY(), lastColor.GetZ(), 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLRenderingApi::DrawRectangle(float x, float y, float width, float height)
{
    DrawRectangle({x, y}, {width, height});
}

void OpenGLRenderingApi::DrawString(const std::wstring &string, glm::vec2 position, const FontFormat &format, int len)
{

}

void OpenGLRenderingApi::DrawFillEllipse(float x, float y, float width, float height)
{

}

void OpenGLRenderingApi::DrawFillEllipse(glm::vec2 pos, glm::vec2 size)
{

}

void OpenGLRenderingApi::DrawFillRectangle(float x, float y, float width, float height)
{
    //DrawFillRectangle({x, y}, {width, height});
}

void OpenGLRenderingApi::DrawFillRectangle(glm::vec2 pos, glm::vec2 size)
{
    if(lastShapeType != ShapeType::FillRectangle)
    {
        lastShape = builder.CreateFillRectangle(pos.x + translation.x, pos.y + translation.y,
                                                size.x, size.y);
        originalData = {pos, size};
        lastShapeType = ShapeType::FillRectangle;
    }
    else
        TransformModel(*lastShape, pos, size);

    lastShape->GetShaderProgram().GetUniformProperties().SetProperty("color", lastColor.GetX(), lastColor.GetY(), lastColor.GetZ(), 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLRenderingApi::SetColor(const Vector4 &color)
{
    lastColor = {color.GetX()/255, color.GetY()/255, color.GetZ()/255, color.GetW()/255};
}

void OpenGLRenderingApi::SetColor(const Vector3 &color)
{
    lastColor = {color.GetX()/255, color.GetY()/255, color.GetZ()/255, 1.0f};

}

void OpenGLRenderingApi::SetThickness(float thickness)
{

}

void OpenGLRenderingApi::SetFontFamily(std::wstring fontFamily)
{

}

void OpenGLRenderingApi::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> OpenGLRenderingApi::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

OpenGLRenderingApi::OpenGLRenderingApi(Window &window, OpenGL::RenderingManager& manager) : window(window), renderingManager(manager)
{
    //CRASH1
    window.AddOnResizeSubscriber(*this);
    viewMatrix = &defaultViewMatrix;
    CreateViewMatrix(window.GetWidth(), window.GetHeight(), *viewMatrix);
    builder.SetProjectionMatrix(viewMatrix);
}

void OpenGLRenderingApi::OnResize(EventResizeInfo e)
{
    CreateViewMatrix(e.GetSize().x, e.GetSize().y, *viewMatrix);
}

void OpenGLRenderingApi::Translate(glm::vec2 translation)
{
    this->translation = translation;
}

void OpenGLRenderingApi::CreateViewMatrix(float width, float height, glm::mat4 &viewMatrix)
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

void OpenGLRenderingApi::TransformModel(OpenGL::Model &model, const glm::vec2 &pos, const glm::vec2 &size)
{
    float sizeXDelta = size.x / originalData.GetSize().x;
    float sizeYDelta = size.y / originalData.GetSize().y;

    model.ResetTransform();
    model.Scale({sizeXDelta, sizeYDelta, 1.0f});
    model.Translate({translation.x, translation.y, 0.0f});
    model.Translate({pos.x, pos.y, 0.0f});
}

void OpenGLRenderingApi::DrawModel(const OpenGL::Model &model)
{
    if(!renderingManager.HasModel(model))
        renderingManager.AddModel(model);

    //Updates the model in the manager
    renderingManager.Move(model);
}
