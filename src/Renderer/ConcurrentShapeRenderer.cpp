//
// Created by erik9 on 5/14/2023.
//
#define _USE_MATH_DEFINES
#include <thread>
#include <vector>
#include "ConcurrentShapeRenderer.h"
#include "FontFormat.h"
#include <future>


void ConcurrentShapeRenderer::DrawModel(const OpenGL::Model &model)
{

}


void ConcurrentShapeRenderer::DrawRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{
    DrawLine(pos, {pos.x + size.x, pos.y, 0});
    DrawLine(pos, {pos.x, pos.y + size.y, 0});
    DrawLine({pos.x + size.x, pos.y, 0}, {pos.x + size.x, pos.y + size.y, 0});
    DrawLine({pos.x, pos.y + size.y, 0}, {pos.x + size.x, pos.y + size.y, 0});
}


void ConcurrentShapeRenderer::DrawString(const std::wstring &string, const glm::vec3 &position, const FontFormat &format)
{

}


void ConcurrentShapeRenderer::DrawFillRectangle(const glm::vec3 &pos, const glm::vec3 &size)
{

    auto rectangles = SplitRectangle({pos, size});
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
    numberOfThreads = 1;//std::thread::hardware_concurrency();
}

void ConcurrentShapeRenderer::DrawEllipse(const glm::vec3 &pos, const glm::vec3 &size)
{
//    int height = size.y;
//    int step = height / numberOfThreads;
//    std::vector<std::future<void>> futures;
//
//    int a = size.x / 2;
//    int b = size.y / 2;
//    int innerA = a - thickness;
//    int innerB = b - thickness;
//
//    for (int i = 0; i < numberOfThreads; ++i) {
//        int startY = i * step;
//        int endY = (i + 1) * step;
//
//        // Handle the last section to cover the entire height
//        if (i == numberOfThreads - 1) {
//            endY = height;
//        }
//
//        futures.push_back(std::async(std::launch::async, &ConcurrentShapeRenderer::DrawEllipseSection, this, startY, endY, pos, size, innerA, innerB));
//    }
//
//    for (auto &future : futures) {
//        future.get();
//    }
}

void ConcurrentShapeRenderer::DrawEllipseSection(int startY, int endY, const glm::vec3 &pos, const glm::vec3 &size, int innerA, int innerB) {
    int a = size.x / 2;
    int b = size.y / 2;
    int centerX = pos.x + a;
    int centerY = pos.y + b;

    int a2 = a * a;
    int b2 = b * b;
    int innerA2 = innerA * innerA;
    int innerB2 = innerB * innerB;

    for (int dy = startY - b; dy < endY - b; ++dy) {
        int y = centerY + dy;

        // Calculate the x range for the current y value
        double xRangeOuter = a * sqrt(1.0 - static_cast<double>(dy * dy) / static_cast<double>(b * b));
        double xRangeInner = innerA * sqrt(1.0 - static_cast<double>(dy * dy) / static_cast<double>(innerB * innerB));
        int startXOuter = centerX - static_cast<int>(xRangeOuter);
        int endXOuter = centerX + static_cast<int>(xRangeOuter);
        int startXInner = centerX - static_cast<int>(xRangeInner);
        int endXInner = centerX + static_cast<int>(xRangeInner);

        // Draw the horizontal line for the outer ellipse
        for (int x = startXOuter; x <= endXOuter; ++x) {
            if (x < startXInner || x > endXInner){
                bufferRenderer.DrawFragment(glm::vec3(x, y, pos.z), color);
            }
        }
    }
}


std::vector<IRectangle>
ConcurrentShapeRenderer::SplitRectangle(const Rectangle &rectangle) const
{
    if (numberOfThreads == 1)
        return {{rectangle.position, rectangle.size}};

    unsigned int height = std::floor(rectangle.size.y / numberOfThreads);
    unsigned int error = static_cast<unsigned int>(rectangle.size.y) % numberOfThreads;
    std::vector<IRectangle> rectangles;
    for(int i = 0; i < numberOfThreads; i++)
    {
        unsigned int y = rectangle.position.y + i * height;
        if(i == numberOfThreads - 1)
            height += error;
        rectangles.push_back({{rectangle.position.x, y}, {rectangle.size.x, height}});
    }

    return rectangles;
}

void ConcurrentShapeRenderer::DrawSingleRectangle(const IRectangle &rectangle)
{
    for(int y = 0; y < rectangle.size.y; y++)
        for(int x = 0; x < rectangle.size.x; x++)
            bufferRenderer.DrawFragment({rectangle.position.x + x, rectangle.position.y + y, 0}, this->color);
}


void ConcurrentShapeRenderer::DrawLine(const glm::vec3 &pos1, const glm::vec3 &pos2)
{
    auto lines = SplitLineIntoSegments({pos1.x, pos1.y}, {pos2.x, pos2.y}, numberOfThreads);
    std::vector<std::future<void>> futures;
    for(auto& line : lines)
    {
        auto future = std::async(std::launch::async, [&]() -> void {
            DrawSingleLine(line);
        });
        futures.push_back(std::move(future));
    }

    for(auto& future : futures)
        future.wait();
}

std::vector<Line> ConcurrentShapeRenderer::SplitLineIntoSegments(const glm::vec2 &pos1, const glm::vec2 &pos2, int numSegments)
{
    std::vector<Line> segments;

    if (numSegments <= 1)
    {
        segments.push_back({pos1, pos2});
        return segments;
    }

    float xStep = (pos2.x - pos1.x) / numSegments;
    float yStep = (pos2.y - pos1.y) / numSegments;

    glm::vec2 startPoint = pos1;
    glm::vec2 endPoint;

    for (int i = 1; i <= numSegments; ++i)
    {
        endPoint = glm::vec2(pos1.x + i * xStep, pos1.y + i * yStep);
        segments.push_back(Line{startPoint, endPoint});
        startPoint = endPoint;
    }

    return segments;
}

void ConcurrentShapeRenderer::DrawSingleLine(const Line &line)
{
    int x1 = static_cast<int>(line.start.x);
    int y1 = static_cast<int>(line.start.y);
    int x2 = static_cast<int>(line.end.x);
    int y2 = static_cast<int>(line.end.y);

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

void ConcurrentShapeRenderer::DrawFillEllipse(const glm::vec3 &pos, const glm::vec3 &size) {
    int height = size.y;
    int subHeight = height / numberOfThreads;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < numberOfThreads; ++i) {
        int startY = i * subHeight;
        int endY = (i + 1) * subHeight;

        // Handle the last section to cover the entire height
        if (i == numberOfThreads - 1) {
            endY = height;
        }

        futures.push_back(std::async(std::launch::async, &ConcurrentShapeRenderer::DrawFillEllipseSection, this, startY, endY, pos, size));
    }

    for (auto &future : futures) {
        future.get();
    }
}

void ConcurrentShapeRenderer::DrawFillEllipseSection(int startY, int endY, const glm::vec3 &pos, const glm::vec3 &size) {
    int a = size.x / 2;
    int b = size.y / 2;
    int centerX = pos.x + a;
    int centerY = pos.y + b;

    for (int dy = startY - b; dy < endY - b; ++dy) {
        int y = centerY + dy;

        int x = 0;

        // Calculate the x range for the current y value
        double xRange = a * sqrt(1.0 - static_cast<double>(dy * dy) / static_cast<double>(b * b));
        int startX = centerX - static_cast<int>(xRange);
        int endX = centerX + static_cast<int>(xRange);

        // Draw the horizontal line within the x range
        for (x = startX; x <= endX; ++x) {
            bufferRenderer.DrawFragment(glm::vec3(x, y, pos.z), color);
        }
    }
}