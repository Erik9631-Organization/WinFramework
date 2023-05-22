//
// Created by erik9 on 5/22/2023.
//
#include "Utils.h"

glm::vec4 TranslateFromCornerToCenter(const glm::vec3 &corner, const glm::vec3 &viewPort)
{
    glm::vec4 translatedInput;
    translatedInput.x = corner.x - (viewPort.x / 2.0f);
    translatedInput.y = corner.y - (viewPort.y / 2.0f);
    translatedInput.z = corner.z - (viewPort.z / 2.0f);
    return translatedInput;
}

