//
// Created by erik9 on 12/21/2022.
//

#ifndef LII_LINEMODEL_H
#define LII_LINEMODEL_H
#include "RenderingModel.h"
#include "glm.hpp"
#include "ModelViewport.h"

class LineModel : public RenderingModel
{
private:
    bool visible = true;
    glm::ivec4 color;
    glm::vec4 startPoint;
    glm::vec4 endPoint;
    Renderer* renderingProvider;
    float width;
    size_t id = -1;
    ModelViewport viewPort;
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

    void SetModelId(size_t id) override;

    const size_t & GetModelId() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    float GetZIndex() override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_LINEMODEL_H
