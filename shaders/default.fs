#version 330 core

const int MAX_POINT_LIGHTS = 2;

in vec3 color;
in vec3 normal;
in vec3 currPos;
in vec2 texCoord;

out vec4 FragColor;

struct BaseLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight
{
    BaseLight base;
    vec3 direction;
};

struct Attenuation
{
    float constant;
    float linear;
    float quad;
};

struct PointLight 
{
    BaseLight base;
    vec3 localPos;
    Attenuation atten;
};

uniform int numPointLights;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform vec3 camPos;

vec4 calcLightInternal(BaseLight light, vec3 lightDir, vec3 normal)
{
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    return ambientColor;
}

vec4 pointLight()
{
    vec3 lightVec = lightPos - currPos;
    float dist = length(lightVec);
    float a = 0.05;
    float b = 0.04;
    float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightVec);

    float diffuse = max(dot(normal, lightDir), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 16);
    float specular = specAmount * specularLight;

    return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight()
{
    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));

    float diffuse = max(dot(normal, lightDir), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 16);
    float specular = specAmount * specularLight;

    return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;
}

void main()
{
    FragColor = pointLight();
}