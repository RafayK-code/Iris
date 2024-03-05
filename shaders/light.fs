#version 330 core
in vec3 color;

out vec4 FragColor;

uniform vec4 lightColor;

void main()
{
    FragColor = lightColor;
}