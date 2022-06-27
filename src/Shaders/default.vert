#version 460 core
#define POINT_LIGHT_MAX 13
#define POINT_LIGHT_OFFSET 0

#define DIRECTIONAL_MAX 1
#define DIRECTIONAL_OFFSET POINT_LIGHT_MAX

#define LIGHTS_MAX POINT_LIGHT_MAX + DIRECTIONAL_MAX

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;
layout (location = 2) in vec3 aNormal;
uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);
uniform vec4 lightPosition = vec4(40, 40, -50, 1.0f);
uniform vec4 directionalLight = vec4(0.0f, 1.0f, 0.5f, 0.0f);
uniform vec4 lightPositions[LIGHTS_MAX];
uniform int usedLights[POINT_LIGHT_MAX];
out flat vec3 viewLightPosition;
out flat vec3 viewDirectionalLight;
out flat vec3 viewLightPositions[LIGHTS_MAX];
out flat int usedLightsInternal[POINT_LIGHT_MAX];
out flat mat4 viewMatrix;
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

   viewLightPositions[DIRECTIONAL_OFFSET] = vec3(view * directionalLight);
   for(int i = 0; i < POINT_LIGHT_MAX; i++)
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