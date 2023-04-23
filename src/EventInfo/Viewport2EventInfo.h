//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2EVENTINFO_H
#define LII_VIEWPORT2EVENTINFO_H
#include "glm.hpp"
#include <any>

class Viewport2EventInfo
{
private:
    glm::vec4 size{0};
    glm::vec4 position{0};
    std::any src;

public:
    Viewport2EventInfo(const glm::vec4 &position, const glm::vec4 &size, const std::any &src)
    {
        this->size = size;
        this->position = position;
        this->src = src;
    }

    [[nodiscard]] const glm::vec4& GetSize() const
    {
        return size;
    }

    [[nodiscard]] const glm::vec4& GetPosition() const
    {
        return position;
    }

    [[nodiscard]] const std::any& GetSource() const
    {
        return src;
    }
};


#endif //LII_VIEWPORT2EVENTINFO_H
