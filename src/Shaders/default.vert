#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;
layout (location = 2) in vec3 aNormal;
uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);
uniform vec4 lightPosition = vec4(40, 40, -50, 1.0f);
out flat vec3 viewLightPosition;
out vec2 TextCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
   TextCoord = aTexturePos;
   vec4 vertexPosition = vec4(aPos, 1.0f);
   mat4 viewModelMatrix = view * model;
   mat3 normalMatrix = mat3(transpose(inverse(viewModelMatrix)));


   FragPos = vec3(viewModelMatrix * vertexPosition);
   Normal = normalMatrix * aNormal;
   viewLightPosition = vec3(view * lightPosition);

   gl_Position =  projection * viewModelMatrix * vertexPosition;
}