//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_LINEPROXY_H
#define LII_LINEPROXY_H
#include "RendererProxy.h"
#include "RenderingConsumer.h"
#include "glm.hpp"

class RenderingConsumer;
class LineModel;

class LineProxy : public RendererProxy
{
private:
    LineModel *lineModel;
    RenderingConsumer *renderingConsumer;
    unsigned long long associatedModelId;
public:
    void SetRenderingConsumer(RenderingConsumer *consumer, unsigned long long associatedModelId);

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

    const glm::vec2& GetStartPoint();
    const glm::vec2& GetEndPoint();

    unsigned long long int &GetAssociatedModelId() override;

};


#endif //LII_LINEPROXY_H
