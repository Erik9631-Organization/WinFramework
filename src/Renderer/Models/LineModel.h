//
// Created by erik9 on 12/21/2022.
//

#ifndef LII_LINEMODEL_H
#define LII_LINEMODEL_H
#include "RenderingModel.h"
#include "glm.hpp"

class LineModel : public RenderingModel
{
private:
    glm::ivec4 color;
    glm::vec4 startPoint;
    glm::vec4 endPoint;
    Renderer* renderingProvider;
    float width;
    size_t id = -1;
public:
    void SetStartPont(const glm::vec4 &pos);
    void SetEndPoint(const glm::vec4 &pos);
    const glm::vec4 & GetStartPoint();
    const glm::vec4 & GetEndPoint();
    void SetColor(const glm::vec4 &color);
    const glm::vec4 & GetColor();
    void SetWidth(float width);
    const float& GetWidth();

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(long long int id) override;

    long long int & GetModelId() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;
};


#endif //LII_LINEMODEL_H
