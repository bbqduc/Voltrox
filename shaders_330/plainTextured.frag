#version 330 core

in vec2 texcoord;

uniform sampler2D sampler;

out vec4 outColor;
void main(void)
{
	outColor = texture(sampler, texcoord);
}
