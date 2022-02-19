//
// Created by Erik on 15/02/22.
//

#include "DefaultShaderProgram.h"
#include "CoreWindow.h"

/**
 *
 * DefaultShaderProgram program
 * program.Add<GraphicsShader>("../Shaders/default.vert")
 * program.Add<GraphicsShader>("../Shaders/default.frag")
 */

/**
 * (A*B)*C = A*(B*C)
 * A*B =! B*A
 */

Shader &DefaultShaderProgram::AddShader(std::unique_ptr<Shader> shader)
{
    Shader& shaderObjRef = *shader;

    //Make sure that the shader source is loaded and compiled
    if(!LoadAndCompile(shaderObjRef))
    {
        CoreWindow::ConsoleWrite("Error, Shader load and compile failed!");
        return shaderObjRef;
    }


    shaders[shader->GetId()] = std::move(shader);
    glAttachShader(programId, shaderObjRef.GetId());
    std::string error = to_string(glGetError());
    CoreWindow::ConsoleWrite("attach failed: " + error);
    return shaderObjRef;
}

Shader &DefaultShaderProgram::GetShader(int id)
{
    return *shaders.at(id);
}

bool DefaultShaderProgram::HasShader(int id)
{
    if(shaders.find(id) == shaders.end())
        return false;
    return true;
}

std::unique_ptr<Shader> DefaultShaderProgram::RemoveShader(int id)
{
    auto findIter = shaders.find(id);
    if(findIter == shaders.end())
        return nullptr;

    std::unique_ptr<Shader> removedShader = std::move(shaders.find(id)->second);
    shaders.erase(findIter);
    return removedShader;
}

unsigned int DefaultShaderProgram::GetId()
{
    return programId;
}

DefaultShaderProgram::DefaultShaderProgram()
{
    programId = glCreateProgram();
    uniformManager = new UniformManager(programId);
}

DefaultShaderProgram::~DefaultShaderProgram()
{
    glDeleteProgram(programId);
    delete uniformManager;
}

bool DefaultShaderProgram::LoadAndCompile(Shader& shader)
{
    if(!shader.IsLoaded())
        if(!shader.Load()) // If loading failed, return error
            return false;


    if(!shader.IsCompiled())
        if(!shader.Compile()) // If compilation failed return error
            return false;
    return true;
}

bool DefaultShaderProgram::Link()
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

void DefaultShaderProgram::Use()
{
    glUseProgram(programId);
}

void DefaultShaderProgram::DeleteShaders()
{
    for( auto it = shaders.begin(); it != shaders.end(); it = shaders.begin())
        shaders.erase(it);
}

const UniformManager &DefaultShaderProgram::GetUniformManager()
{
    return *uniformManager;
}

