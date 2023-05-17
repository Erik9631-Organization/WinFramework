//
// Created by erik9 on 12/21/2022.
//

#ifndef LII_LINEMODEL_H
#define LII_LINEMODEL_H
#include "RenderingModel.h"
#include "glm.hpp"
#include "DefaultViewport.h"

class LineModel : public RenderingModel
{
private:
    bool visible = true;
    glm::ivec4 color;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    Renderer* renderingProvider;
    float size;
    size_t id = -1;
    DefaultViewport viewPort;
public:
    void SetStartPont(const glm::vec3 &pos);
    void SetEndPoint(const glm::vec3 &pos);
    const glm::vec3 & GetStartPoint();
    const glm::vec3 & GetEndPoint();
    void SetColor(const glm::ivec4 &color);
    const glm::ivec4 & GetColor();
    void SetSize(float size);
    [[nodiscard]] float GetSize() const;

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

    void AddViewportSubscriber(ViewportSubscriber &subscriber) override;

    void RemoveViewportSubscriber(ViewportSubscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const ViewportEventInfo &event) override;

    void NotifyOnViewportPositionChanged(const ViewportEventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const ViewportEventInfo &event) override;
};


#endif //LII_LINEMODEL_H
