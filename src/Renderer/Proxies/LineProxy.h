//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_LINEPROXY_H
#define LII_LINEPROXY_H
#include "RenderProxy.h"
#include "RenderingConsumer.h"
#include "glm.hpp"

class RenderingConsumer;
class LineModel;

class LineProxy : public RenderProxy
{
private:
    LineModel *lineModel;
    RenderingConsumer *renderingConsumer;
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

};


#endif //LII_LINEPROXY_H
