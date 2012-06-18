#version 120

uniform mat4 MVP;

attribute vec4 in_Position;

void main()
{
	gl_Position = MVP * vec4(in_Position.xyz, 1.0);
}
