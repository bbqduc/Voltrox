#version 330 core

in vec2 texcoord;

uniform sampler2D sampler;

out vec4 outColor;
void main(void)
{
	outColor = vec4(texture(sampler, texcoord).rgb, 1.0);
}
