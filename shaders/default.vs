#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(aPos, 1);
}