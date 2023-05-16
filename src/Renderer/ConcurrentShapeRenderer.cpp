//
// Created by erik9 on 5/14/2023.
//

#include <thread>
#include <vector>
#include "ConcurrentShapeRenderer.h"
#include "FontFormat.h"
#include <future>


void ConcurrentShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}

void ConcurrentShapeRenderer::DrawLine(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void ConcurrentShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    for(int i = 0 ; i < 1000; i++)
        bufferRenderer.DrawFragment({i, 5, 0}, {255, 0, 0, 255});
}


void ConcurrentShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{

}

void ConcurrentShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{

}

void ConcurrentShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
//    auto rectangles = SplitRectangle({pos, size}, static_cast<float>(numberOfThreads));
//    std::vector<std::future<void>> futures;
//    for(auto& rectangle : rectangles)
//    {
//        auto future = std::async(std::launch::async, [&]() -> void {
//            DrawFillRectangleOnThread(rectangle);
//        });
//        futures.push_back(std::move(future));
//    }
//
//    // Wait for all the tasks to complete
//    for (auto &future : futures)
//        future.wait();
}

void ConcurrentShapeRenderer::SetColor(const glm::ivec4 &color)
{
    this->color = color;
}

void ConcurrentShapeRenderer::SetColor(const glm::ivec3 &color)
{
    this->color = {color, 255};
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
    numberOfThreads = 24;
}

void ConcurrentShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{

}

std::vector<IRectangle> ConcurrentShapeRenderer::SplitRectangle(const Rectangle &rectangle, int numberOfParts)
{
    if (numberOfParts == 1) {
        return {{rectangle.position, rectangle.size}};
    }

    int rows = std::sqrt(numberOfParts);
    int columns = numberOfParts / rows;
    int remainingThreads = numberOfParts - rows * columns;

    int rowHeight = rectangle.size.y / rows;
    int columnWidth = rectangle.size.x / columns;

    std::vector<IRectangle> rectangles;

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            int xPos = rectangle.position.x + column * columnWidth;
            int yPos = rectangle.position.y + row * rowHeight;
            int width = columnWidth;
            int height = rowHeight;

            rectangles.push_back({{xPos, yPos}, {width, height}});
        }
    }
    return rectangles;
}

void ConcurrentShapeRenderer::DrawFillRectangleOnThread(const IRectangle &rectangles)
{
    for(int y = 0; y < rectangles.size.y; y++)
        for(int x = 0; x < rectangles.size.x; x++)
            bufferRenderer.DrawFragment({rectangles.position.x + x, rectangles.position.y + y, 0}, this->color);
}