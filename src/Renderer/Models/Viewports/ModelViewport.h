//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_MODELVIEWPORT_H
#define LII_MODELVIEWPORT_H
#include "glm.hpp"
#include "GraphicsViewport.h"

class ModelViewport : public GraphicsViewport
{
private:
    glm::vec4 viewPortSize = {0,0,0,0};
    glm::vec4 viewPortPosition = {0,0,0,0};
    bool isSet = false;

public:
    [[nodiscard]] bool IsSet() const;

    void ResetViewPort() override;

    void SetViewPortSize(const glm::vec4 &vec4) override;

    void SetViewPortPosition(const glm::vec4 &vec4) override;

    glm::vec4 & GetViewPortSize() override;

    glm::vec4 & GetViewPortPosition() override;

};


#endif //LII_MODELVIEWPORT_H
