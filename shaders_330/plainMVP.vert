#version 330 core

uniform mat4 MVP;

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec3 in_Color;

out vec4 out_Color;

void main()
{
	gl_Position = MVP * vec4(in_Position.xyz, 1.0);
	out_Color = vec4(in_Color, 1.0);
}
