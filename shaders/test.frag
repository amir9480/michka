#version 440 core

in vec2 TexCoord;

uniform sampler2D testTexture;
uniform int test;

layout (location = 0) out vec4 GAlbedo;
layout (location = 1) out vec4 GNormal;

void main()
{
    if (test == 1)
    {
        GNormal = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else if (test == 2)
    {
        GNormal = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else
    {
        GNormal = vec4(0.0, 0.0, 1.0, 1.0);
    }
    GAlbedo = texture(testTexture, TexCoord);
}
