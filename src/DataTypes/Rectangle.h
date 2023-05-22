//
// Created by erik9 on 5/16/2023.
//

#ifndef LII_RECTANGLE_H
#define LII_RECTANGLE_H


#include <glm.hpp>

namespace Lii::DataTypes
{
    struct Rectangle
    {
        glm::vec2 position{0};
        glm::vec2 size{0};
    };

}


#endif //LII_RECTANGLE_H
