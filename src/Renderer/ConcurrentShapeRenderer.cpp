//
// Created by erik9 on 5/14/2023.
//

#include "ConcurrentShapeRenderer.h"
#include "FontFormat.h"

void ConcurrentShapeRenderer::DrawEllipse(float x, float y, float width, float height)
{

}

void ConcurrentShapeRenderer::DrawEllipse(float x, float y, glm::vec4 vec4)
{

}

void ConcurrentShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void ConcurrentShapeRenderer::DrawLine(float x1, float y1, float x2, float y2)
{

}

void ConcurrentShapeRenderer::DrawLine(glm::vec4 pos, glm::vec4 size)
{

}

void ConcurrentShapeRenderer::DrawRectangle(glm::vec3 pos, glm::vec3 size)
{
    bufferRenderer.DrawFragment({50, 50, 0}, {255, 0, 0, 255});
}

void ConcurrentShapeRenderer::DrawRectangle(float x, float y, float width, float height)
{
}

void ConcurrentShapeRenderer::DrawString(const std::wstring &string, glm::vec3 position, const FontFormat &format)
{

}

void ConcurrentShapeRenderer::DrawFillEllipse(float x, float y, float width, float height)
{

}

void ConcurrentShapeRenderer::DrawFillEllipse(glm::vec4 pos, glm::vec4 size)
{

}

void ConcurrentShapeRenderer::DrawFillRectangle(float x, float y, float width, float height)
{

}

void ConcurrentShapeRenderer::DrawFillRectangle(glm::vec3 pos, glm::vec3 size)
{

}

void ConcurrentShapeRenderer::SetColor(const glm::ivec4 &color)
{

}

void ConcurrentShapeRenderer::SetColor(const glm::ivec3 &color)
{

}

void ConcurrentShapeRenderer::SetClippingRectangle(float x, float y, float width, float height)
{

}

void ConcurrentShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{

}

void ConcurrentShapeRenderer::SetThickness(float thickness)
{

}

void ConcurrentShapeRenderer::SetFontFamily(std::wstring fontFamily)
{

}

void ConcurrentShapeRenderer::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> ConcurrentShapeRenderer::CreateFontFormat()
{
    return nullptr;
}

void ConcurrentShapeRenderer::Translate(glm::vec3 translation)
{

}

ConcurrentShapeRenderer::ConcurrentShapeRenderer(BufferRenderer &renderer) : bufferRenderer(renderer)
{

}
