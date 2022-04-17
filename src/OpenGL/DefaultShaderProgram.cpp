//
// Created by Erik on 15/02/22.
//

#include "DefaultShaderProgram.h"
#include "CoreWindow.h"
#include "Shader.h"
#include "UniformProperties.h"


OpenGL::Shader &OpenGL::DefaultShaderProgram::AddShader(std::unique_ptr<Shader> shader)
{
    Shader& shaderObjRef = *shader;

    //Make sure that the shaderProgram source is loaded and compiled
    if(!LoadAndCompile(shaderObjRef))
    {
        CoreWindow::ConsoleWrite("Error, Shader load and compile failed!");
        return shaderObjRef;
    }


    shaders[shader->GetId()] = std::move(shader);
    glAttachShader(programId, shaderObjRef.GetId());
    std::string error = to_string(glGetError());
    if(error != "0")
        CoreWindow::ConsoleWrite("attach failed: " + error);
    return shaderObjRef;
}

OpenGL::Shader &OpenGL::DefaultShaderProgram::GetShader(int id)
{
    return *shaders.at(id);
}

bool OpenGL::DefaultShaderProgram::HasShader(int id)
{
    if(shaders.find(id) == shaders.end())
        return false;
    return true;
}

std::unique_ptr<OpenGL::Shader> OpenGL::DefaultShaderProgram::RemoveShader(int id)
{
    auto findIter = shaders.find(id);
    if(findIter == shaders.end())
        return nullptr;

    std::unique_ptr<Shader> removedShader = std::move(shaders.find(id)->second);
    shaders.erase(findIter);
    return removedShader;
}


OpenGL::DefaultShaderProgram::DefaultShaderProgram()
{
    programId = glCreateProgram();
    uniformManager = new UniformProperties(programId);
}

OpenGL::DefaultShaderProgram::~DefaultShaderProgram()
{
    glDeleteProgram(programId);
    delete uniformManager;
}

bool OpenGL::DefaultShaderProgram::LoadAndCompile(Shader& shader)
{
    if(!shader.IsLoaded())
        if(!shader.Load()) // If loading failed, return error
            return false;


    if(!shader.IsCompiled())
        if(!shader.Compile()) // If compilation failed return error
            return false;
    return true;
}

bool OpenGL::DefaultShaderProgram::Link()
{
    glLinkProgram(programId);
    unsigned int error = glGetError();
    int status = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        glGetProgramInfoLog(programId, 512, NULL, lastError);
        CoreWindow::ConsoleWrite("Error: " + to_string(error) + " " + std::string(lastError));
        return false;
    }
    DeleteShaders();
    return true;
}

void OpenGL::DefaultShaderProgram::Use() const
{
    glUseProgram(programId);
}

void OpenGL::DefaultShaderProgram::DeleteShaders()
{
    for( auto it = shaders.begin(); it != shaders.end(); it = shaders.begin())
        shaders.erase(it);
}

const OpenGL::UniformProperties &OpenGL::DefaultShaderProgram::GetUniformProperties()
{
    return *uniformManager;
}

const unsigned long long int & OpenGL::DefaultShaderProgram::GetId() const
{
    return programId;
}

const std::string &OpenGL::DefaultShaderProgram::GetTag()
{
    return tag;
}

void OpenGL::DefaultShaderProgram::SetTag(const std::string &tag)
{
    this->tag = tag;
}
