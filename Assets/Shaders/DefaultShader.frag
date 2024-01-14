#version 420 core

out vec4 FragColor;

in vec4 o_color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
void main()
{
	FragColor =  texture(ourTexture, TexCoord) * o_color;
};
