//
// Created by erik9 on 5/14/2023.
//

#include "ConcurrentShapeRenderer.h"
#include "FontFormat.h"
void ConcurrentShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void ConcurrentShapeRenderer::DrawLine(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void ConcurrentShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    bufferRenderer.DrawFragment({0, 0, 0}, {255, 0, 0, 255});
}


void ConcurrentShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{

}

void ConcurrentShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void ConcurrentShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    bufferRenderer.DrawFragment({50, 5, 0}, {255, 0, 0, 255});
}

void ConcurrentShapeRenderer::SetColor(const glm::ivec4 &color)
{

}

void ConcurrentShapeRenderer::SetColor(const glm::ivec3 &color)
{

}


void ConcurrentShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{

}

void ConcurrentShapeRenderer::SetThickness(float thickness)
{

}

void ConcurrentShapeRenderer::SetFontFamily(const std::wstring &fontFamily)
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

void ConcurrentShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{

}
