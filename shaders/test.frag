#version 440 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D testTexture;
uniform int test;

void main()
{
    if (test == 1)
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else if (test == 2)
    {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else
    {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    FragColor = texture(testTexture, TexCoord);
}
