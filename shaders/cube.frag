#version 460 core

out vec4 FragColour;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}