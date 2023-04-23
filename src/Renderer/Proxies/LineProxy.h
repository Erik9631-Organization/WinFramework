//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_LINEPROXY_H
#define LII_LINEPROXY_H
#include "RenderProxy.h"
#include "RenderingConsumer.h"
#include "glm.hpp"
#include <vector>

class RenderingConsumer;
class LineModel;

class LineProxy : public RenderProxy
{
private:
    LineModel *lineModel;
    RenderingConsumer *renderingConsumer;
    std::vector<Viewport2Subscriber*> viewPortSubscribers;
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

    void SetWidth(float width);
    const float& GetWidth();

    const glm::vec4 & GetStartPoint();
    const glm::vec4 & GetEndPoint();

    const size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    glm::vec4 &GetViewportSize() override;

    glm::vec4 &GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

};


#endif //LII_LINEPROXY_H
