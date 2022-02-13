//
// Created by Erik on 01/02/22.
//

#include "OpenGLRenderer.h"
#include "Vector2.h"
#include <memory>
#include "FontFormat.h"
#include <Windows.h>
#include <gl/GL.h>

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
    //clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//load identity matrix

    glColor3f(0.0f,0.0f,1.0f); //blue color

    glPointSize(10.0f);//set point size to 10 pixels

    glBegin(GL_POINTS); //starts drawing of points
    glVertex3f(1.0f,1.0f,0.0f);//upper-right corner
    glVertex3f(-1.0f,-1.0f,0.0f);//lower-left corner
    glEnd();//end drawing of points
}

void OpenGLRenderer::FillRectangle(Vector2 pos, Vector2 size)
{

}

void OpenGLRenderer::SetColor(const Vector4 &color)
{

}

void OpenGLRenderer::SetColor(const Vector3 &color)
{

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
    return nullptr;
}
