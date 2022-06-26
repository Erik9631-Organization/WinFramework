#version 460 core
#define LIGHT_COUNT 100

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;
layout (location = 2) in vec3 aNormal;
uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);
uniform vec4 lightPosition = vec4(40, 40, -50, 1.0f);
uniform vec4 directionalLight = vec4(0.0f, 1.0f, 0.5f, 0.0f);
uniform vec4 lightPositions[LIGHT_COUNT];
uniform int usedLights[LIGHT_COUNT];
out flat vec3 viewLightPosition;
out flat vec3 viewDirectionalLight;
out flat vec3 viewLightPositions[LIGHT_COUNT];
out flat int usedLightsInternal[LIGHT_COUNT];
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
   viewLightPosition = vec3(view * lightPosition);
   viewDirectionalLight = vec3(view * directionalLight);
   for(int i = 0; i < LIGHT_COUNT; i++)
   {
      if(usedLights[i] == 0)
      {
         continue;
      }
      viewLightPositions[i] == vec3(view * lightPositions[i]);
   }
   usedLightsInternal = usedLights;

   gl_Position =  projection * viewModelMatrix * vertexPosition;
}