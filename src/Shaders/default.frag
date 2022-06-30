#version 460 core

#define MAX_DIRECTIONAL 20
#define MAX_POINT_LIGHTS 20
#define LIGHTS_MAX 20

struct Material
{
	vec3 ambientStrength;
	vec3 specular;
	vec3 diffuse;
	float specStrength;
};

struct Fragment
{
	int lightVectorCount;
	vec3 lightVectors[LIGHTS_MAX];
	vec3 lightColors[LIGHTS_MAX];
	vec3 reflectionVector[LIGHTS_MAX];
	float lightVectorLengths[LIGHTS_MAX];
	float attenuation[LIGHTS_MAX];
	vec3 diffuseProperty;
	vec3 specularProperty;
};

struct Light
{
	vec3 pos;
	int enabled;
	vec3 color;
};

uniform Light directionalLights[MAX_DIRECTIONAL];
uniform Light pointLights[MAX_POINT_LIGHTS];

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

uniform vec3 lightColor = vec3(0.5f, 0.5f, 0.5f);
uniform vec3 directionalLightColor = vec3(0.5f, 0.5f, 0.2f);
uniform Material material;
float globalLinearTerm = 0.2f;
float globalQuadraticTerm = 0.5f;


float CalculateAttenuation(float distance, float linearTerm, float quadraticTerm)
{
	float constantTerm = 1.0f;
	return 1.0/(constantTerm + (linearTerm * distance) + (quadraticTerm * pow(distance,2)) );
}

Fragment CalculateFragmentVectors(Fragment fragment)
{
	int lightIter = 0;
	int fragmentIndex = 0;
	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if(pointLights[i].enabled == 0)
		continue;
		vec3 lightVector = normalize(pointLights[i].pos - FragPos);
		fragment.lightVectors[fragmentIndex] = lightVector;
		fragment.lightVectorLengths[fragmentIndex] = length(lightVector);
		fragment.reflectionVector[fragmentIndex] = reflect(lightVector, Normal);
		fragment.attenuation[fragmentIndex] = CalculateAttenuation(fragment.lightVectorLengths[fragmentIndex], globalLinearTerm, globalQuadraticTerm);
		fragment.lightColors[fragmentIndex] = pointLights[i].color;
		if(fragmentIndex+1 > LIGHTS_MAX)
		continue;

		fragment.lightVectorCount = fragmentIndex+1;

		fragmentIndex++;
	}

	for(int i = 0; i < MAX_DIRECTIONAL; i++)
	{
		if(directionalLights[i].enabled == 0)
		continue;

		vec3 lightVector = normalize(directionalLights[i].pos);
		fragment.lightVectors[fragmentIndex] = lightVector;
		fragment.lightVectorLengths[fragmentIndex] = -1;
		fragment.reflectionVector[fragmentIndex] = reflect(lightVector, Normal);
		fragment.attenuation[fragmentIndex] = 0.8f;
		fragment.lightVectorCount = fragmentIndex+1;
		fragment.lightColors[fragmentIndex] = pointLights[i].color;
		fragment.lightColors[fragmentIndex] = directionalLights[i].color;

		if(fragmentIndex+1 > LIGHTS_MAX)
		continue;

		fragmentIndex++;
	}
	return fragment;
}

Fragment CalculateDiffuseProperty(Fragment fragment)
{
	int counter = 0;
	for(int i = 0; i < fragment.lightVectorCount; i++, counter++)
	{
		vec3 currentVector = fragment.lightVectors[i];
		float rayStrength = max( dot(currentVector, normalize(Normal)), 0.0f);
		vec3 diffuseProperty = fragment.lightColors[i] * rayStrength * material.diffuse * fragment.attenuation[i];
		fragment.diffuseProperty += diffuseProperty;
	}
	return fragment;
}

Fragment CalculateSpecularProperty(Fragment fragment)
{
	vec3 cameraVector = normalize(CameraPos - FragPos);
	for(int i = 0; i < fragment.lightVectorCount; i++)
	{
		float angle = max(dot(fragment.reflectionVector[i], cameraVector), 0.0f);
		float strength = pow(angle, material.specStrength);
		fragment.specularProperty += fragment.lightColors[i] * strength * material.specular * fragment.attenuation[i];
	}
	return fragment;
}



//vec3 DiffuseLight()
//{
//	vec3 lightVector = normalize(viewLightPosition - FragPos);
//	float distance = length(lightVector);
//	float attenuation = CalculateAttenuation(distance, globalLinearTerm, globalQuadraticTerm);
//
//	float rayStrength = max( dot(lightVector, normalize(Normal)), 0.0f);
//	return lightColor * rayStrength * material.diffuse * attenuation;
//}

//vec3 DirectionalDiffuse()
//{
//	vec3 normalizedDirectional = normalize(viewDirectionalLight);
//	float strength = max( dot(normalizedDirectional, normalize(Normal)), 0.0f);
//	return directionalLightColor * strength * material.diffuse;
//}
//
//vec3 DirectionalSpecular()
//{
//	vec3 reflectionVector = reflect(normalize(viewDirectionalLight), Normal);
//	vec3 cameraVector = normalize(CameraPos - FragPos);
//	float angle = max(dot(reflectionVector, cameraVector), 0.0f);
//	float specular = pow(angle, material.specStrength);
//	return directionalLightColor * specular * material.specular;
//}
//
//vec3 SpecularLight()
//{
//	vec3 reflectionVector = reflect(normalize(FragPos - viewLightPosition), Normal);
//	float distance = length(reflectionVector);
//	float attenuation = CalculateAttenuation(distance, globalLinearTerm, globalQuadraticTerm);
//
//
//	vec3 cameraVector = normalize(CameraPos - FragPos);
//	float angle = max(dot(reflectionVector, cameraVector), 0.0f);
//	float specular = pow(angle, material.specStrength);
//	return lightColor * specular * material.specular * attenuation;
//}

void main()
{
	Fragment fragment;
	fragment = CalculateFragmentVectors(fragment);
	fragment = CalculateDiffuseProperty(fragment);
	//fragment = CalculateSpecularProperty(fragment);

	//FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(diffuseLight + material.ambientStrength + specularLight, 1.0f) * directionalLight;
	FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(fragment.diffuseProperty + material.ambientStrength, 1.0f);
}