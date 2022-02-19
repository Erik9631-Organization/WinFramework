//
// Created by Erik on 13/02/22.
//

#include "GraphicsShader.h"
#include <fstream>
#include <glew.h>
#include "CoreWindow.h"
unsigned int GraphicsShader::GetId()
{
    return shaderId;
}

bool GraphicsShader::Compile()
{
    glCompileShader(shaderId);
    int compileStatus = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE)
    {
        compiled = false;
        glGetShaderInfoLog(shaderId, 512, NULL, lastError);
        CoreWindow::ConsoleWrite(std::string(lastError));

    }

    else
        compiled = true;

    return compiled;
}

void GraphicsShader::SetShaderSrc(std::wstring path, unsigned int shaderType)
{
    //Clear previous shader
    glDeleteShader(shaderId);
    shaderId = glCreateShader(shaderType);

    this->path = std::move(path);
    this->type = shaderType;
}

std::wstring GraphicsShader::GetShaderPath()
{
    return path;
}

bool GraphicsShader::Load()
{
    std::ifstream fileStream;
    fileStream.open(path, std::fstream::in);
    if(!fileStream.is_open())
        return loaded;

    char value;
    while( fileStream.get(value) )
        this->shaderSource += value;

    const char* result = shaderSource.c_str();
    glShaderSource(shaderId, 1, &result, NULL);

    loaded = true;
    return loaded;
}

const std::string & GraphicsShader::GetShaderSource()
{
    return shaderSource;
}

bool GraphicsShader::IsLoaded()
{
    return loaded;
}

unsigned int GraphicsShader::GetShaderType()
{
    return type;
}

GraphicsShader::GraphicsShader(std::wstring path, unsigned int shaderType)
{
    SetShaderSrc(std::move(path), shaderType);
}

GraphicsShader::~GraphicsShader()
{
    glDeleteShader(shaderId);
}

bool GraphicsShader::IsCompiled()
{
    return compiled;
}

