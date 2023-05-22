//
// Created by erik9 on 5/21/2023.
//

#include "AggShapeRenderer.h"
#include "FontFormat.h"
#include "BufferRenderer.h"
#include "agg_renderer_scanline.h"
#include <tracy/Tracy.hpp>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_ellipse.h>
#include <agg_scanline_p.h>
#include "Utils.h"
#include "agg_renderer_raster_text.h"
#include "agg_glyph_raster_bin.h"
#include "agg_embedded_raster_fonts.h"
#include "AggFontFormat.h"
#include <agg_font_cache_manager.h>


void AggShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size, bool drawFromCenter)
{
    ZoneScoped;
    auto editedPosition = position;
    if(!drawFromCenter)
        editedPosition = TranslateFromCornerToCenter(position, size);

    renderer->line_color(color);
    renderer->ellipse(editedPosition.x, editedPosition.y, size.x/2, size.y/2);
}

void AggShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void AggShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{
    ZoneScoped;
    renderer->line_color(color);
    renderer->line(pos1.x, pos1.y, pos2.x, pos2.y);
}

void AggShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    ZoneScoped;
    renderer->line_color(color);
    renderer->rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
}

void AggShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{
    agg::glyph_raster_bin<agg::pixfmt_bgra32> glyphRaster{agg::gse5x7};
    agg::renderer_raster_htext_solid<agg::renderer_mclip<agg::pixfmt_bgra32>,
            agg::glyph_raster_bin<agg::pixfmt_bgra32>> textRaster(*baseRenderer, glyphRaster);
    textRaster.color(color);
    textRaster.render_text(position.x - 20, position.y, string.c_str(), true);
}

void AggShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size, bool drawFromCenter)
{
    ZoneScoped;
//    agg::rasterizer_scanline_aa rasterizer;
//    agg::scanline_p8 scanline;
//    agg::ellipse ellipse(pos.x, pos.y, size.x, size.y);
//    rasterizer.add_path(ellipse);
//    agg::render_scanlines_aa_solid(rasterizer, scanline, *baseRenderer, color);
    auto editedPosition = pos;
    if(!drawFromCenter)
        editedPosition = TranslateFromCornerToCenter(pos, size);

    renderer->fill_color(color);
    renderer->solid_ellipse(editedPosition.x, editedPosition.y, size.x/2, size.y/2);
}

void AggShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    ZoneScoped;
    renderer->fill_color(color);
    renderer->solid_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
}

void AggShapeRenderer::SetColor(const glm::ivec4 &color)
{
    this->color.r = color.r / 255.0f;
    this->color.g = color.g / 255.0f;
    this->color.b = color.b / 255.0f;
    this->color.a = color.a / 255.0f;
}

void AggShapeRenderer::SetColor(const glm::ivec3 &color)
{
    this->color.r = color.r / 255.0f;
    this->color.g = color.g / 255.0f;
    this->color.b = color.b / 255.0f;
    this->color.a = 1.0f;
}

void AggShapeRenderer::SetClippingRectangle(const glm::vec2 &pos, const glm::vec2 &size)
{
    baseRenderer->reset_clipping(true);
    baseRenderer->add_clip_box(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
}

void AggShapeRenderer::SetThickness(float thickness)
{

}

void AggShapeRenderer::SetFontFamily(const std::wstring &fontFamily)
{

}

void AggShapeRenderer::SetFontSize(float fontSize)
{

}

std::unique_ptr<FontFormat> AggShapeRenderer::CreateFontFormat()
{
    return std::unique_ptr<FontFormat>(new AggFontFormat());
}

void AggShapeRenderer::Translate(glm::vec3 translation)
{

}

void AggShapeRenderer::SetScreenBuffer(BufferRenderer &buffer)
{
    auto screenBuffer = buffer.GetScreenBuffer();
    bufferRenderer = &buffer;
    this->buffer = std::make_unique<agg::rendering_buffer>(reinterpret_cast<unsigned char*>(screenBuffer.GetBuffer()), screenBuffer.GetWidth(),
            screenBuffer.GetHeight(), screenBuffer.GetWidth() * 4);
    pixelFormat = std::make_unique<agg::pixfmt_bgra32>(*this->buffer);
    baseRenderer = new agg::renderer_mclip<agg::pixfmt_bgra32>(*pixelFormat);
    renderer = new agg::renderer_primitives<agg::renderer_mclip<agg::pixfmt_bgra32>>(*baseRenderer);
}
