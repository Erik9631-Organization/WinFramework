#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;
layout (location = 2) in vec3 aNormal;
uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);

out vec2 TextCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
   TextCoord = aTexturePos;
   vec4 vertexPosition = vec4(aPos, 1.0f);
   mat4 viewModelMatrix = view * model;

   //Fixes that if object is non-uniform scaled, normal is not perpedicular anymore
   mat3 normalMatrix = mat3(transpose(inverse(viewModelMatrix)));
   FragPos = vec3(viewModelMatrix * vertexPosition);
   Normal = normalMatrix * aNormal;

   gl_Position =  projection * viewModelMatrix * vertexPosition;
}