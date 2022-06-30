//
// Created by Erik on 13/03/22.
//

#ifndef LII_CAMERA_H
#define LII_CAMERA_H
#include "glm.hpp"
#include "RelativeMovement.h"

namespace OpenGL
{
    class Camera : public RelativeMovement
    {
    public:
        virtual const glm::mat4 & GetViewMatrix() const = 0;
    };
}

#endif //LII_CAMERA_H
