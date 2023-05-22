//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CONCURRENTSHAPERENDERER_H
#define LII_CONCURRENTSHAPERENDERER_H


#include "ShapeRenderer.h"
#include "Rectangle.h"
#include "IRectangle.h"
#include "Line.h"
class BufferRenderer;


class ConcurrentShapeRenderer : public ShapeRenderer
{
private:
    BufferRenderer* bufferRenderer;
    Lii::DataTypes::Buffer<unsigned int> buffer;
    unsigned int numberOfThreads = 2;
    unsigned int color = 0;
    float thickness = 1.0f;
    Lii::DataTypes::Rectangle clippingRectangle;
    bool clippingSet = false;

    std::vector<Lii::DataTypes::Line> SplitLineIntoSegments(const glm::vec2 &pos1, const glm::vec2 &pos2, int numSegments);
    [[nodiscard]] std::vector<Lii::DataTypes::IRectangle> SplitRectangle(const Lii::DataTypes::Rectangle& rectangle) const;

    void DrawSingleRectangle(const Lii::DataTypes::IRectangle &rectangle);
    void DrawSingleLine(const Lii::DataTypes::Line &line);
    void DrawFillEllipseSection(int startY, int endY, const glm::vec3 &pos, const glm::vec3 &size);
    void DrawEllipseSection(int startY, int endY, const glm::vec3 &pos, const glm::vec3 &size, int innerA, int innerB);
    [[nodiscard]] bool IsOutsideBounds(unsigned int x, unsigned int y) const;
    [[nodiscard]] bool IsRectangleOutsideBounds(const Lii::DataTypes::IRectangle& rectangle) const;
    void DrawFragment(const glm::ivec3& position, const glm::ivec4 &color);
public:
    explicit ConcurrentShapeRenderer();

    void DrawModel(const OpenGL::Model &model) override;

    void DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2) override;

    void DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;

    void DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format) override;

    void DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size, bool drawFromCenter = true) override;

    void DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size) override;

    void SetColor(const glm::ivec4 &color) override;

    void SetColor(const glm::ivec3 &color) override;

    void SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size) override;

    void SetThickness(float thickness) override;

    void SetFontFamily(const std::wstring &fontFamily) override;

    void SetFontSize(float fontSize) override;

    std::unique_ptr<FontFormat> CreateFontFormat() override;

    void Translate(glm::vec3 translation) override;

    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size, bool drawFromCenter = true) override;

    void SetScreenBuffer(BufferRenderer &buffer) override;

};


#endif //LII_CONCURRENTSHAPERENDERER_H
