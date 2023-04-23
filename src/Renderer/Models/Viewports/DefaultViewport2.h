//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_DEFAULTVIEWPORT2_H
#define LII_DEFAULTVIEWPORT2_H
#include "glm.hpp"
#include "Viewport2.h"
#include <vector>

class DefaultViewport2 : public Viewport2
{
private:
    glm::vec4 viewPortSize = {0,0,0,0};
    glm::vec4 viewPortPosition = {0,0,0,0};
    bool isSet = false;
    std::vector<Viewport2Subscriber*> subscribers;

public:
    [[nodiscard]] bool IsViewportSet() const override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    glm::vec4 & GetViewportSize() override;

    glm::vec4 & GetViewportPosition() override;

    void AddViewport2Subscriber(Viewport2Subscriber *subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber *subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;
};


#endif //LII_DEFAULTVIEWPORT2_H
