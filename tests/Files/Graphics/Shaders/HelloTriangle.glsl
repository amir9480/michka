#if COMPILING_VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}

#endif // COMPILING_VERTEX_SHADER

#if COMPILING_FRAGMENT_SHADER

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}

#endif // COMPILING_FRAGMENT_SHADER
