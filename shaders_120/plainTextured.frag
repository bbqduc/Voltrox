#version 120

varying vec2 texcoord;

uniform sampler2D sampler;

void main(void)
{
	gl_FragColor = vec4(1.0f);//texture2D(sampler, texcoord);
}
