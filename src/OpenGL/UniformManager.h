//
// Created by Erik on 19/02/22.
//

#ifndef LII_UNIFORMMANAGER_H
#define LII_UNIFORMMANAGER_H

#include <string>
#include <windows.h>
#include <glew.h>
#include <vector>
class UniformManager
{
private:
    const unsigned int& shaderProgramId;
public:
    UniformManager(const unsigned int& shaderProgramId) : shaderProgramId(shaderProgramId)
    {

    }

    template<typename ... type>
    void SetUniform(void (*glUniform)(int, type ...), const std::string& name, type ... args) const
    {

        int uniformShader = glGetUniformLocation(shaderProgramId, name.c_str());
        if(uniformShader == -1)
            return;
        glUniform(uniformShader, args ... );
    }

    template<typename type>
    void SetUniform(void (*glUniform)(int, type ...), const std::string& name, const std::vector<type>& args) const
    {
        int uniformShader = glGetUniformLocation(shaderProgramId, name.c_str());
        if(uniformShader == -1)
            return;
        glUniform(uniformShader, args.size(), args.data());
    }
};


#endif //LII_UNIFORMMANAGER_H
