#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 color;
out vec3 normal;
out vec3 currPos;
out vec2 texCoord;

uniform mat4 vp;
uniform mat4 model;

void main()
{
    currPos = vec3(model * vec4(aPos, 1.0f));

    gl_Position = vp * vec4(currPos, 1);
    color = aColor;
    normal = aNorm;
    texCoord = aTex;
}