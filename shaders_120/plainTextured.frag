#version 120

varying vec2 ex_Texcoord;

uniform sampler2D sampler;

void main(void)
{
	gl_FragColor = texture2D(sampler, ex_Texcoord);
}
