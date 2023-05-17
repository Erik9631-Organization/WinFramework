//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_LINEPROXY_H
#define LII_LINEPROXY_H
#include "RenderProxy.h"
#include "RenderingConsumer.h"
#include "glm.hpp"
#include "RenderingProxyMessageSender.h"
#include "DefaultViewport.h"
#include <vector>

class RenderingConsumer;
class LineModel;

class LineProxy : public RenderProxy
{
private:
    static constexpr glm::vec3 defaultVec = glm::vec4{0, 0, 0, 0};
    static constexpr glm::ivec4 defaultColorVec = glm::vec4{0, 0, 0, 0};

    LineModel *model = nullptr;
    RenderingConsumer *renderingConsumer = nullptr;
    RenderingProxyMessageSender messageSender;
    std::vector<ViewportSubscriber*> viewPortSubscribers;
public:
    /**
     * Sets viewPortSize of the starting point of the line
     * @param position - viewPortSize of the starting point of the line
     */
    void SetStartPosition(const glm::vec3& position);

    /**
     * Sets viewPortSize of the end point of the line
     * @param position - viewPortSize of the end point of the line
    */
    void SetEndPosition(const glm::vec3& position);

    void SetSize(float width);
    float GetSize();

    const glm::vec3 & GetStartPoint();
    const glm::vec3 & GetEndPoint();

    const size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

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

    void SetColor(const glm::ivec4& color);

    const glm::ivec4& GetColor();

};


#endif //LII_LINEPROXY_H
