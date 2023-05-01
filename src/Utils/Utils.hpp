//
// Created by erik9 on 4/19/2023.
//

#ifndef LII_UTILS_HPP
#define LII_UTILS_HPP
#include <glm.hpp>

glm::vec4 TranslateFromCornerToCenter(const glm::vec3 &corner, const glm::vec3 &viewPort)
{
    glm::vec4 translatedInput;
    translatedInput.x = corner.x - (viewPort.x / 2.0f);
    translatedInput.y = corner.y - (viewPort.y / 2.0f);
    translatedInput.z = corner.z - (viewPort.z / 2.0f);
    return translatedInput;
}


#endif //LII_UTILS_HPP
