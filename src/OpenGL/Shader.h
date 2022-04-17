//
// Created by Erik on 13/02/22.
//

#ifndef LII_SHADER_H
#define LII_SHADER_H
#include <string>

namespace OpenGL
{
    class Shader
    {
    public:
        virtual unsigned int GetId() = 0;
        virtual bool Compile() = 0;
        virtual bool Load() = 0;
        virtual bool IsLoaded() = 0;
        virtual bool IsCompiled() = 0;
        virtual unsigned int GetShaderType() = 0;
        virtual ~Shader() = default;
    };
}


#endif //LII_SHADER_H
