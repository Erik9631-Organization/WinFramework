#version 460 core
#define LIGHT_COUNT 100

struct Material
{
	vec3 ambientStrength;
	vec3 specular;
	vec3 diffuse;
	float specStrength;
};
vec3 defaultAmbient = vec3(0.1f, 0.1f, 0.1f);
vec3 defaultSpecular = vec3(0.5f, 0.5f, 0.5f);
vec3 defaultDiffuseElement = vec3(1.0f, 1.0f, 1.0f);

vec3 CameraPos = {0,0,0};

out vec4 FragColor;
in vec3 FragPos;
in vec2 TextCoord;
in vec3 Normal;
uniform vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

uniform sampler2D inputTexture;
in flat vec3 viewLightPosition;
in flat vec3 viewDirectionalLight;
in flat vec4 viewLightPositions[LIGHT_COUNT];
in flat int usedLightsInternal[LIGHT_COUNT];

uniform vec3 lightColor = vec3(0.5f, 0.5f, 0.5f);
uniform vec3 directionalLightColor = vec3(0.5f, 0.5f, 0.2f);
uniform Material material;
float globalLinearTerm = 0.0f;
float globalQuadraticTerm = 0.5f;


float CalculateAttenuation(float distance, float linearTerm, float quadraticTerm)
{
	float constantTerm = 1.0f;
	return 1.0/(constantTerm + (linearTerm * distance) + (quadraticTerm * pow(distance,2)) );
}

vec3 DiffuseLight()
{
    vec3 lightVector = normalize(viewLightPosition - FragPos);
	float distance = length(lightVector);
	float attenuation = CalculateAttenuation(distance, globalLinearTerm, globalQuadraticTerm);

    float rayStrength = max( dot(lightVector, normalize(Normal)), 0.0f);
    return lightColor * rayStrength * material.diffuse * attenuation;
}

vec3 DirectionalDiffuse()
{
	vec3 normalizedDirectional = normalize(viewDirectionalLight);
	float strength = max( dot(normalizedDirectional, normalize(Normal)), 0.0f);
	return directionalLightColor * strength * material.diffuse;
}

vec3 DirectionalSpecular()
{
	vec3 reflectionVector = reflect(normalize(viewDirectionalLight), Normal);
	vec3 cameraVector = normalize(CameraPos - FragPos);
	float angle = max(dot(reflectionVector, cameraVector), 0.0f);
	float specular = pow(angle, material.specStrength);
	return directionalLightColor * specular * material.specular;
}

vec3 SpecularLight()
{
	vec3 reflectionVector = reflect(normalize(FragPos - viewLightPosition), Normal);
	float distance = length(reflectionVector);
	float attenuation = CalculateAttenuation(distance, globalLinearTerm, globalQuadraticTerm);


	vec3 cameraVector = normalize(CameraPos - FragPos);
	float angle = max(dot(reflectionVector, cameraVector), 0.0f);
	float specular = pow(angle, material.specStrength);
	return lightColor * specular * material.specular * attenuation;
}

void main()
{
	vec3 diffuseLight = DiffuseLight();
   	vec3 specularLight = SpecularLight();
	vec3 directionalLight = DirectionalDiffuse();
	vec3 directionalSpecular = DirectionalSpecular();
	//FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(diffuseLight + material.ambientStrength + specularLight, 1.0f) * directionalLight;
	FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(directionalLight + material.ambientStrength + directionalSpecular, 1.0f);
}