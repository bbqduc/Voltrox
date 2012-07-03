#version 330 core

smooth in vec2 ex_Texcoord;

uniform sampler2D sampler;

out vec4 outColor;
void main(void)
{
	outColor = texture(sampler, ex_Texcoord);
}
