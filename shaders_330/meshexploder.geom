#version 330 core

uniform float timeSinceExplosion;
uniform mat4 MVP;
uniform vec3 localExplosionCenter;

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
//layout(line_strip, max_vertices=3) out;

smooth in vec2 geom_Texcoord[];
in vec3 geom_Normal[];

smooth out vec2 ex_Texcoord;

vec3 rotateVec(vec4 q, vec3 v)
{
	return v + 2.0*cross(cross(v, q.xyz)+q.w*v, q.xyz);
//	vec3 temp = cross(q.xyz, v) + q.w * v;
//	return (cross(temp, -q.xyz) + dot(q.xyz,v) * q.xyz + q.w * temp);
}

mat4 translationMatrix(vec3 vector)
{
	mat4 m = mat4(1.0f);
	m[3] = vec4(vector, 1.0f);

	return m;
}

vec4 rotateq(vec3 axis, float angle)
{
	float c = cos(angle/2);
	float s = sin(angle/2);
	return vec4(c, s*axis.x, s*axis.y, s*axis.z);
}

void main()
{
	vec3 faceNormal = (geom_Normal[0] + geom_Normal[1] + geom_Normal[2]) / 3.0f;
	vec4 p1 = gl_in[0].gl_Position;
	vec4 p2 = gl_in[1].gl_Position;
	vec4 p3 = gl_in[2].gl_Position;

	vec3 center = (p1.xyz + p2.xyz+ p3.xyz);
	center /= 3.0f;

	vec3 d = center - localExplosionCenter;
	float force = timeSinceExplosion / length(d);
	d *= force;
//	vec4 q = normalize(vec4(force,1.0f/force,-force,force*force));
	
	vec4 q = rotateq(faceNormal, force);

	gl_Position = MVP * vec4(d + center + rotateVec(q, p1.xyz-center), 1.0);
	ex_Texcoord = geom_Texcoord[0];
	EmitVertex();
	gl_Position = MVP * vec4(d + center + rotateVec(q, p2.xyz-center), 1.0);
	ex_Texcoord = geom_Texcoord[1];
	EmitVertex();
	gl_Position = MVP * vec4(d + center + rotateVec(q, p3.xyz-center), 1.0);
	ex_Texcoord = geom_Texcoord[2];
	EmitVertex();

	EndPrimitive();
}
