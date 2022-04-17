//
// Created by Erik on 19/02/22.
//

#ifndef LII_UNIFORM_H
#define LII_UNIFORM_H

#include "UniformProperties.h"

namespace OpenGL
{
    class Uniform
    {
    public:
        virtual const UniformProperties& GetUniformProperties() = 0;
    };
}


#endif //LII_UNIFORM_H
