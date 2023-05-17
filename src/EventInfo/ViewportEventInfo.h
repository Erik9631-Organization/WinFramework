//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORTEVENTINFO_H
#define LII_VIEWPORTEVENTINFO_H
#include "glm.hpp"
#include "Event.h"

class ViewportEventInfo : public Event
{
private:
    glm::vec3 size{0};
    glm::vec3 position{0};
    EventSource* src;

public:
    ViewportEventInfo(const glm::vec3 &position, const glm::vec3 &size, EventSource *src)
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


#endif //LII_VIEWPORTEVENTINFO_H
