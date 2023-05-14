//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CONCURRENTSHAPERENDERER_H
#define LII_CONCURRENTSHAPERENDERER_H


#include "ShapeRenderer.h"

class ConcurrentShapeRenderer : public ShapeRenderer
{
private:
    BufferRenderer& bufferRenderer;
public:
    ConcurrentShapeRenderer(BufferRenderer& renderer);
    void DrawEllipse(float x, float y, float width, float height) override;

    void DrawEllipse(float x, float y, glm::vec4 vec4) override;

    void DrawModel(const OpenGL::Model &model) override;

    void DrawLine(float x1, float y1, float x2, float y2) override;

    void DrawLine(glm::vec4 pos, glm::vec4 size) override;

    void DrawRectangle(glm::vec3 pos, glm::vec3 size) override;

    void DrawRectangle(float x, float y, float width, float height) override;

    void DrawString(const std::wstring &string, glm::vec3 position, const FontFormat &format) override;

    void DrawFillEllipse(float x, float y, float width, float height) override;

    void DrawFillEllipse(glm::vec4 pos, glm::vec4 size) override;

    void DrawFillRectangle(float x, float y, float width, float height) override;

    void DrawFillRectangle(glm::vec3 pos, glm::vec3 size) override;

    void SetColor(const glm::ivec4 &color) override;

    void SetColor(const glm::ivec3 &color) override;

    void SetClippingRectangle(float x, float y, float width, float height) override;

    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

    void SetThickness(float thickness) override;

    void SetFontFamily(std::wstring fontFamily) override;

    void SetFontSize(float fontSize) override;

    std::unique_ptr<FontFormat> CreateFontFormat() override;

    void Translate(glm::vec3 translation) override;

};


#endif //LII_CONCURRENTSHAPERENDERER_H
