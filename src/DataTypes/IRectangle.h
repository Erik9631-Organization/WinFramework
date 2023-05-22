//
// Created by erik9 on 5/16/2023.
//

#ifndef LII_IRECTANGLE_H
#define LII_IRECTANGLE_H
#include <glm.hpp>
namespace Lii::DataTypes
{
    struct IRectangle
    {
        glm::ivec2 position{0};
        glm::ivec2 size{0};
    };

}


#endif //LII_IRECTANGLE_H
