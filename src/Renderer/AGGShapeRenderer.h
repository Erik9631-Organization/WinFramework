//
// Created by erik9 on 5/21/2023.
//

#ifndef LII_AGGSHAPERENDERER_H
#define LII_AGGSHAPERENDERER_H
#include "ShapeRenderer.h"

class AGGShapeRenderer : public ShapeRenderer
{
public:
    void SetBufferRenderer(BufferRenderer &bufferRenderer) override;

    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size) override;

    void DrawModel(const OpenGL::Model &model) override;

    void DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2) override;

    void DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;

    void DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format) override;

    void DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size) override;

    void DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;

    void SetColor(const glm::ivec4 &color) override;

    void SetColor(const glm::ivec3 &color) override;

    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

    void SetThickness(float thickness) override;

    void SetFontFamily(const std::wstring &fontFamily) override;

    void SetFontSize(float fontSize) override;

    std::unique_ptr<FontFormat> CreateFontFormat() override;

    void Translate(glm::vec3 translation) override;

};


#endif //LII_AGGSHAPERENDERER_H
