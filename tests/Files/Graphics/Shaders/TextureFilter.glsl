#if COMPILING_VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexcoord;

uniform mat4x4 wvp;

out vec2 texcoord;

void main()
{
    gl_Position = vec4(aPos, 1.0) * wvp;
    texcoord = aTexcoord;
}

#endif // COMPILING_VERTEX_SHADER

#if COMPILING_FRAGMENT_SHADER

uniform sampler2D diffuse;

in vec2 texcoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(diffuse, texcoord);
}

#endif // COMPILING_FRAGMENT_SHADER
