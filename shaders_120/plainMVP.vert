#version 120

uniform mat4 MVP;

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec3 in_Color;

varying vec4 ex_color;

void main()
{
	gl_Position = MVP * vec4(in_Position, 1.0);
	ex_color = vec4(in_Color, 1.0);
}
