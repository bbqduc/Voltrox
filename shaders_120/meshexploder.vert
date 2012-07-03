#version 120

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_Texcoord;

varying vec2 ex_Texcoord;
varying vec2 geom_Texcoord;
varying vec3 geom_Normal;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	geom_Texcoord = in_Texcoord;
	ex_Texcoord = in_Texcoord;
	geom_Normal = in_Normal;
}
