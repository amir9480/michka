#version 440 core

in vec3 aPos;
in vec3 aNormal;
in vec3 aTangent;
in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
