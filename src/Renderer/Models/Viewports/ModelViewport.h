//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_MODELVIEWPORT_H
#define LII_MODELVIEWPORT_H
#include "glm.hpp"
#include "Viewport2.h"
#include <vector>

class ModelViewport : public Viewport2
{
private:
    glm::vec3 viewPortSize{0};
    glm::vec3 viewPortPosition{0};
    bool isSet = false;
    std::vector<Viewport2Subscriber*> subscribers;

public:
    [[nodiscard]] bool IsViewportSet() const override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_MODELVIEWPORT_H
