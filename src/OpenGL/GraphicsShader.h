//
// Created by Erik on 13/02/22.
//

#ifndef LII_GRAPHICSSHADER_H
#define LII_GRAPHICSSHADER_H
#include "Shader.h"

class GraphicsShader : public Shader
{
public:
    GraphicsShader(std::wstring path, unsigned int shaderType);
    void SetShaderSrc(std::wstring path, unsigned int shaderType);
    std::wstring GetShaderPath();
    unsigned int GetId() override;
    bool Compile() override;
    bool Load() override;
    const std::string & GetShaderSource();
    bool IsLoaded() override;
    unsigned int GetShaderType() override;
    ~GraphicsShader() override;
    bool IsCompiled() override;
private:
    GraphicsShader() = default;
    unsigned int shaderId = 0;
    unsigned int type = 0;
    std::wstring path;
    std::string shaderSource;
    bool loaded = false;
    bool compiled = false;
    char lastError[512];
};


#endif //LII_GRAPHICSSHADER_H
