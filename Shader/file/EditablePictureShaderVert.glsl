#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec2 aTexCoords1;
layout(location = 3) in vec2 aTexCoords2;
layout(location = 4) in vec2 aTexCoords3;
layout(location = 5) in vec4 aColor;
layout(location = 6) in vec4 aColor1;
layout(location = 7) in vec4 aColor2;
layout(location = 8) in vec4 aColor3;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;
uniform vec3 prams;

out vec2 TexCoord;
out vec4 Color;
out vec3 Prams;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoords);
    Color = color;
    Prams = prams;
}
