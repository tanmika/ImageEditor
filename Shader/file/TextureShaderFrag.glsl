#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, TexCoord) * Color;
}
