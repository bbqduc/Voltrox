#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_Texcoord;

smooth out vec2 geom_Texcoord;
out vec3 geom_Normal;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	geom_Texcoord = in_Texcoord;
	geom_Normal = in_Normal;
}