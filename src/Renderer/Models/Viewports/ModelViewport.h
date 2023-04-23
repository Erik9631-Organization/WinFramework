//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_MODELVIEWPORT_H
#define LII_MODELVIEWPORT_H
#include "glm.hpp"
#include "Viewport2.h"

class ModelViewport : public Viewport2
{
private:
    glm::vec4 viewPortSize = {0,0,0,0};
    glm::vec4 viewPortPosition = {0,0,0,0};
    bool isSet = false;

public:
    [[nodiscard]] bool IsSet() const;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    glm::vec4 & GetViewportSize() override;

    glm::vec4 & GetViewportPosition() override;

};


#endif //LII_MODELVIEWPORT_H
