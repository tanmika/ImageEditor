#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 Color;
in vec3 Prams;

uniform sampler2D Texture;
uniform vec2 TextureSize;

vec4 Blur()
{
    vec4 result = vec4(0.0);
    vec2 tex_offset = 1.0 / TextureSize;
    float step = 1 + Prams.x / 70.0;
    for (int i = -5; i <= 5; i++) //
    {
        for (int j = -5; j <= 5; j++)
        {
            result += texture(Texture, TexCoord + vec2(tex_offset.x * i * step, tex_offset.y * j * step));
        }
    }
    result /= 121.0;
    return result;
}


vec4 Sharpen()
{
    vec4 sharpened = vec4(0.0);

    vec3 offsets[9] = vec3[](
    vec3(-1.0, -1.0, -1.0), vec3(0.0, -1.0, -1.0), vec3(1.0, -1.0, -1.0),
    vec3(-1.0, 0.0, -1.0),  vec3(0.0, 0.0, 9.0),   vec3(1.0, 0.0, -1.0),
    vec3(-1.0, 1.0, -1.0),  vec3(0.0, 1.0, -1.0),  vec3(1.0, 1.0, -1.0)
    );

    for (int i = 0; i < 9; i++) {
        vec2 offset = vec2(offsets[i].x, offsets[i].y) / TextureSize;
        sharpened += texture(Texture, TexCoord + offset) * offsets[i].z;
    }

    return sharpened;
}

vec4 applyGrayscale(vec4 color, float amount)
{
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    vec4 grayscaleColor = vec4(vec3(gray), color.a);
    return mix(color, grayscaleColor, amount / 100.0);
}

void main()
{
    vec4 color = texture(Texture, TexCoord) * Color;

    // 模糊处理
    if (Prams.x > 0.0) {
        color = mix(color, Blur(), Prams.x/100.0);
    }

    // 锐化处理
    if (Prams.y > 0.0) {
        color = mix(color, Sharpen(), Prams.y / 100.0);
    }

    // 黑白化处理
    if (Prams.z > 0.0) {
        color = applyGrayscale(color, Prams.z);
    }

    FragColor = color;
}
