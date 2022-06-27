#version 460 core
#define POINT_LIGHT_MAX 13
#define POINT_LIGHT_OFFSET 0

#define DIRECTIONAL_MAX 1
#define DIRECTIONAL_OFFSET POINT_LIGHT_MAX

#define LIGHTS_MAX POINT_LIGHT_MAX + DIRECTIONAL_MAX

struct Material
{
	vec3 ambientStrength;
	vec3 specular;
	vec3 diffuse;
	float specStrength;
};

struct Fragment
{
	int directionalOffset;
	int lightVectorCount;
	vec3 lightVectors[LIGHTS_MAX];
	vec3 reflectionVector[LIGHTS_MAX];
	float lightVectorLengths[LIGHTS_MAX];
	float attenuation[LIGHTS_MAX];
	vec3 diffuseProperty;
	vec3 specularProperty;
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
in flat vec3 viewLightPositions[LIGHTS_MAX];
in flat int usedLightsInternal[POINT_LIGHT_MAX];

uniform vec3 lightColor = vec3(0.5f, 0.5f, 0.5f);
uniform vec3 directionalLightColor = vec3(0.5f, 0.5f, 0.2f);
uniform Material material;
float globalLinearTerm = 0.0f;
float globalQuadraticTerm = 0.5f;

int currentLight = 0;

int GetNextLightIndex()
{
	while(usedLightsInternal[currentLight] == 0 && currentLight < POINT_LIGHT_MAX)
	{
		currentLight++;
	}
	return currentLight;
}

void RestartLightIter()
{
	currentLight = 0;
}

float CalculateAttenuation(float distance, float linearTerm, float quadraticTerm)
{
	float constantTerm = 1.0f;
	return 1.0/(constantTerm + (linearTerm * distance) + (quadraticTerm * pow(distance,2)) );
}

Fragment CalculateFragmentVectors(Fragment fragment)
{
	RestartLightIter();
	int lightIter = 0;
	int fragmentIndex = 0;
	while( (lightIter = GetNextLightIndex()) < (POINT_LIGHT_MAX))
	{
		vec3 lightVector = normalize(viewLightPositions[lightIter] - FragPos);
		fragment.lightVectors[fragmentIndex] = lightVector;
		fragment.lightVectorLengths[fragmentIndex] = length(lightVector);
		fragment.reflectionVector[fragmentIndex] = reflect(lightVector, Normal);
		fragment.attenuation[fragmentIndex] = CalculateAttenuation(fragment.lightVectorLengths[fragmentIndex], globalLinearTerm, globalQuadraticTerm);
		fragmentIndex++;
	}

	fragmentIndex++;

	//Add directional light
	fragment.lightVectors[fragmentIndex] = viewLightPositions[DIRECTIONAL_OFFSET] ;
	fragment.reflectionVector[fragmentIndex] = reflect(viewLightPositions[DIRECTIONAL_OFFSET] , Normal);
	fragment.lightVectorLengths[fragmentIndex] = -1;
	fragment.attenuation[fragmentIndex] = 0.8f;
	fragment.directionalOffset = fragmentIndex;

	fragment.lightVectorCount = fragmentIndex+1;
	return fragment;
}

Fragment CalculateDiffuseProperty(Fragment fragment)
{
	int counter = 0;
	for(int i = 0; i < fragment.lightVectorCount; i++, counter++)
	{
		vec3 currentVector = fragment.lightVectors[i];

		float rayStrength = max( dot(currentVector, normalize(Normal)), 0.0f);
		vec3 diffuseProperty = lightColor * rayStrength * material.diffuse * fragment.attenuation[i];
		fragment.diffuseProperty += diffuseProperty;
	}
	return fragment;
}

Fragment CalculateSpecularProperty(Fragment fragment)
{
	vec3 cameraVector = normalize(CameraPos - FragPos);
	for(int i = 0; i < fragment.lightVectorCount; i++)
	{
		float angle = max(dot(fragment.reflectionVector[fragment.directionalOffset], cameraVector), 0.0f);
		float strength = pow(angle, material.specStrength);
		fragment.specularProperty += lightColor * strength * material.specular * fragment.attenuation[i];
	}
	return fragment;
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
	Fragment fragment;
	fragment = CalculateFragmentVectors(fragment);
	fragment = CalculateDiffuseProperty(fragment);
	fragment = CalculateSpecularProperty(fragment);

	//FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(diffuseLight + material.ambientStrength + specularLight, 1.0f) * directionalLight;
	FragColor = (texture(inputTexture, TextCoord) + color)  * vec4(fragment.diffuseProperty + fragment.specularProperty  + material.ambientStrength, 1.0f);
}