//
// Created by erik9 on 12/21/2022.
//

#ifndef LII_LINEMODEL_H
#define LII_LINEMODEL_H
#include "RenderingModel.h"
#include "glm.hpp"
#include "Vector4.h"

class LineModel : public RenderingModel
{
private:
    Vector4 color;
    glm::vec2 startPoint;
    glm::vec2 endPoint;
    Renderer* renderer;
    float width;
public:
    void SetStartPont(const glm::vec2& pos);
    void SetEndPoint(const glm::vec2& pos);
    const glm::vec2& GetStartPoint();
    const glm::vec2& GetEndPoint();
    void SetColor(const Vector4& color);
    const Vector4& GetColor();
    void SetWidth(float width);
    const float& GetWidth();

    void Redraw() override;

    void SetRenderer(Renderer *renderer) override;
};


#endif //LII_LINEMODEL_H
