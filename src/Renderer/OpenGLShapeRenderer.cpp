//
// Created by Erik on 01/02/22.
//

#include "OpenGLShapeRenderer.h"
#include <memory>
#include "FontFormat.h"
#include "Model.h"
#include "Window.h"
#include "EventResizeInfo.h"
#include "ShaderProgram.h"
#include "UniformProperties.h"
#include "GdiFontFormat.h"
#include "Core/Windows/WindowsCore.h"

void OpenGLShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{

}

void OpenGLShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
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
    lastShape->GetShaderProgram().GetUniformProperties().SetProperty("color", lastColor.x, lastColor.y, lastColor.z, 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{

}


void OpenGLShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void OpenGLShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
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

    lastShape->GetShaderProgram().GetUniformProperties().SetProperty("color", lastColor.x, lastColor.y, lastColor.z, 1.0f);
    //lastShape->UpdateUniform();
}

void OpenGLShapeRenderer::SetColor(const glm::ivec4 &color)
{
    lastColor = {color.x/255, color.y/255, color.z/255, color.w/255};
}

void OpenGLShapeRenderer::SetColor(const glm::ivec3 &color)
{
    lastColor = {color.x/255, color.y/255, color.z/255, 1.0f};

}

void OpenGLShapeRenderer::SetThickness(float thickness)
{

}

void OpenGLShapeRenderer::SetFontFamily(const std::wstring &fontFamily)
{

}

void OpenGLShapeRenderer::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> OpenGLShapeRenderer::CreateFontFormat()
{
    return std::make_unique<GdiFontFormat>();
}

OpenGLShapeRenderer::OpenGLShapeRenderer(Window &window, OpenGL::RenderingManager& manager) : window(window), renderingManager(manager)
{
    window.AddOnResizeSubscriber(*this);
    viewMatrix = &defaultViewMatrix;
    CreateViewMatrix(window.GetSize().x, window.GetSize().y, *viewMatrix);
    builder.SetProjectionMatrix(viewMatrix);
}

void OpenGLShapeRenderer::OnResize(EventResizeInfo e)
{
    CreateViewMatrix(e.GetSize().x, e.GetSize().y, *viewMatrix);
}

void OpenGLShapeRenderer::Translate(glm::vec3 translation)
{
    this->translation = translation;
}

void OpenGLShapeRenderer::CreateViewMatrix(float width, float height, glm::mat4 &viewMatrix)
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

void OpenGLShapeRenderer::TransformModel(OpenGL::Model &model, const glm::vec2 &pos, const glm::vec2 &size)
{
    float sizeXDelta = size.x / originalData.GetSize().x;
    float sizeYDelta = size.y / originalData.GetSize().y;

    model.ResetTransform();
    model.Scale({sizeXDelta, sizeYDelta, 1.0f});
    model.Translate({translation.x, translation.y, 0.0f});
    model.Translate({pos.x, pos.y, 0.0f});
}

void OpenGLShapeRenderer::DrawModel(const OpenGL::Model &model)
{
    if(!renderingManager.HasModel(model))
        renderingManager.AddModel(model);

    //Updates the model in the manager
    renderingManager.Move(model);
}

void OpenGLShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{

}

void OpenGLShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{

}