#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

uniform mat4 vp;
uniform mat4 model;
out vec3 color;

void main()
{
    gl_Position = vp * model * vec4(aPos, 1);
    color = aColor;
}