//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2EVENTINFO_H
#define LII_VIEWPORT2EVENTINFO_H
#include "glm.hpp"
#include "Event.h"

class Viewport2EventInfo : public Event
{
private:
    glm::vec3 size{0};
    glm::vec3 position{0};
    EventSource* src;

public:
    Viewport2EventInfo(const glm::vec3 &position, const glm::vec3 &size, EventSource *src)
    {
        this->size = size;
        this->position = position;
        this->src = src;
    }

    [[nodiscard]] const glm::vec3 & GetSize() const
    {
        return size;
    }

    [[nodiscard]] const glm::vec3 & GetPosition() const
    {
        return position;
    }

    [[nodiscard]] EventSource * GetSource() const override
    {
        return src;
    }
};


#endif //LII_VIEWPORT2EVENTINFO_H
