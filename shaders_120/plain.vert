#version 120

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_Texcoord;

varying vec3 ex_Normal;
varying vec2 ex_Texcoord;

void main()
{
	gl_Position = vec4(in_Position, 1.0);

	ex_Normal = in_Normal;
	ex_Texcoord = in_Texcoord;
}
