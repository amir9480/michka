#if COMPILING_VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec2 aTexCoord;

uniform mat4x4 wvp;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0) * wvp;
	TexCoord = aTexCoord;
}

#endif // COMPILING_VERTEX_SHADER

#if COMPILING_FRAGMENT_SHADER

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

#endif // COMPILING_FRAGMENT_SHADER
