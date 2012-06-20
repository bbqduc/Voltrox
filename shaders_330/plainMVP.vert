#version 330 core

uniform mat4 MVP;

layout(location=0) in vec3 in_Position;
//layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_Texcoord;

out vec2 texcoord;

void main()
{
	gl_Position = MVP * vec4(in_Position, 1.0);
	texcoord = in_Texcoord;
}
