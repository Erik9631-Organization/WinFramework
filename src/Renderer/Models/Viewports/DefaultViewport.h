//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_DEFAULTVIEWPORT_H
#define LII_DEFAULTVIEWPORT_H
#include "glm.hpp"
#include "Viewport.h"
#include <vector>

class DefaultViewport : public Viewport
{
private:
    glm::vec3 viewPortSize{0};
    glm::vec3 viewPortPosition{0};
    bool isSet = false;
    std::vector<ViewportSubscriber*> subscribers;

public:
    [[nodiscard]] bool IsViewportSet() const override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void AddViewportSubscriber(ViewportSubscriber &subscriber) override;

    void RemoveViewportSubscriber(ViewportSubscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const ViewportEventInfo &event) override;

    void NotifyOnViewportPositionChanged(const ViewportEventInfo &event) override;

    void NotifyOnViewportReset(const ViewportEventInfo &event) override;
};


#endif //LII_DEFAULTVIEWPORT_H
