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
     * Sets position of the starting point of the line
     * @param position - position of the starting point of the line
     */
    void SetStartPosition(const glm::vec3& position);

    /**
     * Sets position of the end point of the line
     * @param position - position of the end point of the line
    */
    void SetEndPosition(const glm::vec3& position);

    void SetWidth(float width);
    const float& GetWidth();

    const glm::vec4 & GetStartPoint();
    const glm::vec4 & GetEndPoint();

    size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

};


#endif //LII_LINEPROXY_H
