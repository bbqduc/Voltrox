#version 330 core

in vec2 texcoord;

out vec4 out_Color;

uniform sampler2D sampler;

void main()
{
	out_Color = texture(sampler, texcoord);
}