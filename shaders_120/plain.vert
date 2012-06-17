#version 120

attribute vec4 in_Position;

void main()
{
	gl_Position = vec4(in_Position.xyz, 1.0);
}
