#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_Texcoord;

out vec3 ex_Normal;
out vec2 ex_Texcoord;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	ex_Normal = in_Normal;
	ex_Texcoord = in_Texcoord;
}
