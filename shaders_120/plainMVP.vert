#version 120

uniform mat4 MVP;

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_Texcoord;

varying vec2 ex_Texcoord;

void main()
{
	gl_Position = MVP * vec4(in_Position, 1.0);
	ex_Texcoord=in_Texcoord;
//	ex_color = vec4(in_Color, 1.0);
}
