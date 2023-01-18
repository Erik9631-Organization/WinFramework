//
// Created by erik9 on 1/17/2023.
//

#ifndef LII_MODELVIEWPORT_H
#define LII_MODELVIEWPORT_H
#include "vec2.hpp"

class ModelViewport
{
private:
    glm::vec2 viewPortSize = {0,0};
    glm::vec2 viewPortPosition = {0,0};

public:
    void ResetPosition();
    void ResetSize();

    void SetViewPortSize(const glm::vec2 &size);
    void SetViewPortPosition(const glm::vec2 &position);
    void SetViewPortX(float x);
    void SetViewPortY(float y);
    void SetViewPortWidth(float width);
    void SetViewPortHeight(float height);

    const glm::vec2& GetViewPortSize() const;
    const glm::vec2& GetViewPortPosition() const;
    float GetViewPortX() const;
    float GetViewPortY() const;
    float GetViewPortWidth() const;
    float GetViewPortHeight() const;

};


#endif //LII_MODELVIEWPORT_H
