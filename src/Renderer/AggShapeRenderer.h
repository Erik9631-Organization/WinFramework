//
// Created by erik9 on 5/21/2023.
//

#ifndef LII_AGGSHAPERENDERER_H
#define LII_AGGSHAPERENDERER_H
#include "ShapeRenderer.h"
#include "agg_renderer_primitives.h"
#include "agg_renderer_mclip.h"
#include "agg_pixfmt_rgba.h"
class AggShapeRenderer : public ShapeRenderer
{
private:
    agg::rgba color;
    BufferRenderer* bufferRenderer;
    std::unique_ptr<agg::rendering_buffer> buffer;
    std::unique_ptr<agg::pixfmt_bgra32> pixelFormat;
    agg::renderer_mclip<agg::pixfmt_bgra32>* baseRenderer;
    agg::renderer_primitives<agg::renderer_mclip<agg::pixfmt_bgra32>>* renderer;
public:
    void DrawEllipse(const glm::vec3 &position, const glm::vec3 &size, bool drawFromCenter = true) override;

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

    void SetScreenBuffer(BufferRenderer &buffer) override;

};


#endif //LII_AGGSHAPERENDERER_H
