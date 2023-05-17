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

void ConcurrentShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{
    int x1 = static_cast<int>(pos1.x);
    int y1 = static_cast<int>(pos1.y);
    int x2 = static_cast<int>(pos2.x);
    int y2 = static_cast<int>(pos2.y);

    int xDistance = abs(x2 - x1);
    int yDistance = abs(y2 - y1);

    int xAxis = x1 < x2 ? 1 : -1;
    int yAxis = y1 < y2 ? 1 : -1;

    int err = (xDistance > yDistance ? xDistance : -yDistance) / 2;
    int e2;

    float half_thickness = thickness / 2.0f;
    int t = static_cast<int>(ceil(half_thickness));

    while (true) {
        for (int i = -t; i <= t; ++i) {
            for (int j = -t; j <= t; ++j) {
                if (sqrt(i * i + j * j) <= half_thickness) {
                    glm::vec3 position(x1 + i, y1 + j, 0);
                    bufferRenderer.DrawFragment(position, color);
                }
            }
        }

        if (x1 == x2 && y1 == y2) {
            break;
        }

        e2 = err;

        if (e2 > -xDistance) {
            err -= yDistance;
            x1 += xAxis;
        }

        if (e2 < yDistance) {
            err += xDistance;
            y1 += yAxis;
        }
    }
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
    auto rectangles = SplitRectangle({pos, size}, threadFactorX, threadFactorY);
    std::vector<std::future<void>> futures;
    for(auto& rectangle : rectangles)
    {
        auto future = std::async(std::launch::async, [&]() -> void {
            DrawSingleRectangle(rectangle);
        });
        futures.push_back(std::move(future));
    }

    // Wait for all the tasks to complete
    for (auto &future : futures)
        future.wait();
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
    numberOfThreads = std::thread::hardware_concurrency();
    FindThreadFactors();
}

void ConcurrentShapeRenderer::DrawEllipse(const glm::vec3 &position, const glm::vec3 &size)
{

}

std::vector<IRectangle>
ConcurrentShapeRenderer::SplitRectangle(const Rectangle &rectangle, unsigned int rows, unsigned int columns) const
{
    if (numberOfThreads == 1) {
        return {{rectangle.position, rectangle.size}};
    }

    int columnWidth = rectangle.size.x / columns;
    int rowHeight = rectangle.size.y / rows;
    int errorX = static_cast<unsigned int>(rectangle.size.x) % columns;
    int errorY = static_cast<unsigned int>(rectangle.size.y) % rows;

    std::vector<IRectangle> rectangles;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int xPos = rectangle.position.x + column * columnWidth;
            int yPos = rectangle.position.y + row * rowHeight;
            int width = columnWidth;
            int height = rowHeight;

            rectangles.push_back({{xPos, yPos}, {width, height}});
        }
    }
    rectangles.back().size.x += errorX;
    rectangles.back().size.y += errorY;
    return rectangles;
}

void ConcurrentShapeRenderer::DrawSingleRectangle(const IRectangle &rectangle)
{
    for(int y = 0; y < rectangle.size.y; y++)
        for(int x = 0; x < rectangle.size.x; x++)
            bufferRenderer.DrawFragment({rectangle.position.x + x, rectangle.position.y + y, 0}, this->color);
}

void ConcurrentShapeRenderer::FindThreadFactors()
{
    int closestFactor = std::floor((float)std::sqrt(numberOfThreads));
    while(numberOfThreads % closestFactor != 0)
        closestFactor--;
    threadFactorX = closestFactor;
    threadFactorY = numberOfThreads / closestFactor;
}
