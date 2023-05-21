//
// Created by erik9 on 5/21/2023.
//

#include "AGGShapeRenderer.h"
#include "FontFormat.h"

void AGGShapeRenderer::SetBufferRenderer(BufferRenderer &bufferRenderer)
{

}

void AGGShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{

}

void AGGShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void AGGShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{

}

void AGGShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void AGGShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{

}

void AGGShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void AGGShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void AGGShapeRenderer::SetColor(const glm::ivec4 &color)
{

}

void AGGShapeRenderer::SetColor(const glm::ivec3 &color)
{

}

void AGGShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{

}

void AGGShapeRenderer::SetThickness(float thickness)
{

}

void AGGShapeRenderer::SetFontFamily(const std::wstring &fontFamily)
{

}

void AGGShapeRenderer::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> AGGShapeRenderer::CreateFontFormat()
{
    return nullptr;
}

void AGGShapeRenderer::Translate(glm::vec3 translation)
{

}
