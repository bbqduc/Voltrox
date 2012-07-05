#version 330 core

smooth in vec2 ex_Texcoord;

uniform sampler2D sampler;
uniform float alpha;

out vec4 outColor;
void main(void)
{
	outColor = vec4(texture(sampler, ex_Texcoord).rgb, alpha);
}