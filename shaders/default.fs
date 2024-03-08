#version 330 core
in vec3 color;
in vec3 normal;
in vec3 currPos;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;

//for specular
uniform vec3 camPos;

void main()
{
    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - currPos);

    float diffuse = max(dot(normal, lightDir), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 8);
    float specular = specAmount * specularLight;

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}