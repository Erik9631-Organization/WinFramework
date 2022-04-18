//
// Created by Erik on 15/02/22.
//

#ifndef LII_DEFAULTSHADERPROGRAM_H
#define LII_DEFAULTSHADERPROGRAM_H
#include "ShaderProgram.h"
#include <map>
#include "Shader.h"
#include <windows.h>
#include <glew.h>
#include <wglew.h>
#include <CoreWindow.h>
#include "CoreWindow.h"
#include "UniformProperties.h"

namespace OpenGL
{
    class DefaultShaderProgram : public ShaderProgram
    {
    public:
        DefaultShaderProgram();
        Shader &AssembleShader(std::unique_ptr<Shader> shader) override;
        Shader &GetShader(int id) override;
        bool HasShader(int id) override;
        std::unique_ptr<Shader> RemoveShader(int id) override;
        template<typename Type, typename ... Args>
        Type& Add(Args ... constructorArgs)
        {
            auto shaderObj = std::make_unique<Type>( constructorArgs ...);
            Type& shaderObjRef = *shaderObj;

            //Make sure that the shaderProgram source is loaded and compiled
            if(!LoadAndCompile(shaderObjRef))
            {
                CoreWindow::ConsoleWrite("Error, Shader load and compilation failed!");
                return shaderObjRef;
            }

            shaders.emplace(shaderObjRef.GetId(), std::move(shaderObj));

            glAttachShader(programId, shaderObjRef.GetId());
            return shaderObjRef;
        }
        ~DefaultShaderProgram() override;
        bool Link() override;
        void Use() const override;
        const UniformProperties &GetUniformProperties() override;
        const unsigned long long int & GetId() const override;
        const std::string& GetTag() override;
        void SetTag(const std::string& tag) override;
    private:
        UniformProperties* uniformManager;
        bool LoadAndCompile(Shader& shader);
        char lastError[512];
        unsigned int programId;
        std::map<unsigned int, std::unique_ptr<Shader>>shaders;
        void DeleteShaders();
        std::string tag;
    };
}


#endif //LII_DEFAULTSHADERPROGRAM_H
