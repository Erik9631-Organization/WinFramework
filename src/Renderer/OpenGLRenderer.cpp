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
#include "UniformManager.h"
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

}

void OpenGLRenderer::DrawRectangle(float x, float y, float width, float height)
{

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
    FillRectangle({x, y}, {width, height});
}

void OpenGLRenderer::FillRectangle(Vector2 pos, Vector2 size)
{
    if(lastShapeType != ShapeType::Rectangle)
    {
        lastShape = builder.CreateRectangle(pos.GetX() + translation.GetX(), pos.GetY() + translation.GetX(), size.GetX(), size.GetY());
        lastDrawdata = {pos, size};
        lastShapeType = ShapeType::Rectangle;
    }
    else
    {
        //lastShape->ResetTransform();
        float sizeXDelta = size.GetX() / lastDrawdata.GetSize().GetX();
        float sizeYDelta = size.GetY() / lastDrawdata.GetSize().GetY();

        float posXDelta = (pos.GetX()) - lastDrawdata.GetPosition().GetX();
        float posYDelta = (pos.GetY()) - lastDrawdata.GetPosition().GetY();

        lastShape->Scale({sizeXDelta, sizeYDelta, 1.0f});
        lastShape->Translate({posXDelta, posYDelta, 0.0f});

        //Save the last parameters;
        lastDrawdata = {pos, size};
    }
    lastShape->GetShader().GetUniformManager().SetUniform(glUniform4f, "color", lastColor.GetX(), lastColor.GetY(), lastColor.GetZ(), 1.0f);
    lastShape->Draw();
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

OpenGLRenderer::OpenGLRenderer(Window& window) : window(window)
{
    window.AddOnResizeSubscriber(*this);
    viewMatrix = std::make_unique<glm::mat4>(1.0f);
    float screenWidth = window.GetWidth();
    float screenHeight = window.GetHeight();
    *viewMatrix =
    {
    2.0f/screenWidth, 0, 0, -1,
    0, -2.0f/screenHeight, 0, 1,
    0, 0, 1, 0,
    0, 0, 0, 1
    };
    *viewMatrix = glm::transpose(*viewMatrix);
    builder.SetViewMatrix(viewMatrix);
}

void OpenGLRenderer::OnResize(EventResizeInfo e)
{
    Vector2 size = e.GetSize();

    float screenWidth = size.GetX();
    float screenHeight = size.GetY();
    *viewMatrix =
    {
        2.0f/screenWidth, 0, 0, -1,
        0, -2.0f/screenHeight, 0, 1,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    *viewMatrix = glm::transpose(*viewMatrix);
}

void OpenGLRenderer::Translate(Vector2 translation)
{
    this->translation = translation;
}
