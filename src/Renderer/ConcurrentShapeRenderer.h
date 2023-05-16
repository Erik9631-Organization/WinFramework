//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CONCURRENTSHAPERENDERER_H
#define LII_CONCURRENTSHAPERENDERER_H


#include "ShapeRenderer.h"
#include "Rectangle.h"
#include "IRectangle.h"

class ConcurrentShapeRenderer : public ShapeRenderer
{
private:
    BufferRenderer& bufferRenderer;
    unsigned int numberOfThreads = 2;
    glm::ivec4 color{255, 255, 255, 255};

    std::vector<IRectangle> SplitRectangle(const Rectangle& rectangle, int numberOfParts);

    void DrawFillRectangleOnThread(const IRectangle &rectangles);

public:
    explicit ConcurrentShapeRenderer(BufferRenderer& renderer);

    void DrawModel(const OpenGL::Model &model) override;

    void DrawLine(const glm::vec3 &pos, const glm::vec3 &size) override;

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

    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size) override;

};


#endif //LII_CONCURRENTSHAPERENDERER_H
