#version 330 core

uniform float timeSinceExplosion;
uniform mat4 MVP;
uniform vec3 localExplosionCenter;

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

smooth in vec2 geom_Texcoord[];
in vec3 geom_Normal[];

smooth out vec2 ex_Texcoord;

mat4 rotationMatrix(vec3 axis, float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	float u = 1.0 - c;

	mat4 rotmat;

	rotmat[0][0] = axis.x*axis.x*u + c;		
	rotmat[1][0] = axis.y*axis.x*u - (axis.z*s);
	rotmat[2][0] = axis.z*axis.x*u + (axis.y*s);

	rotmat[0][1] = axis.x*axis.y*u + (axis.z*s);
	rotmat[1][1] = axis.y*axis.y*u + c;		
	rotmat[2][1] = axis.z*axis.y*u - (axis.x*s);

	rotmat[0][2] = axis.x*axis.z*u - (axis.y*s);
	rotmat[1][2] = axis.x*axis.z*u - (axis.y*s);
	rotmat[2][2] = axis.z*axis.z*u + c;			
	rotmat[3][3] = 1.0f;

	return rotmat;
}

mat4 translationMatrix(vec3 vector)
{
	mat4 m = mat4(1.0f);
	m[3] = vec4(vector, 1.0f);

	return m;
}

void main()
{
	vec3 faceNormal = (geom_Normal[0] + geom_Normal[1] + geom_Normal[2]) / 3.0f;


	vec4 p1 = gl_in[0].gl_Position;
	vec4 p2 = gl_in[1].gl_Position;
	vec4 p3 = gl_in[2].gl_Position;

	vec3 center = (p1.xyz + p2.xyz+ p3.xyz);
	center /= 3.0f;

	p1 = vec4(center, 1.0);
	p2 = vec4(faceNormal, 1.0) + p1;
	p3 = p2 + p1 + vec4(0,0.5,0,1);
	vec3 d = center - localExplosionCenter;
	float force = 1.0f / length(d);
	d *= timeSinceExplosion * force;
	mat4 rotmat = rotationMatrix(vec3(1.0,0.0,0.0), timeSinceExplosion);

	// Don't know why translationMatrix(center) and -center don't work here on linux
	// On windows it was fine
	mat4 transform = MVP * translationMatrix(d);// * rotmat; //translationMatrix(d) * translationMatrix(p1.xyz) * rotmat * translationMatrix(-p1.xyz);

	gl_Position = transform * p1;
	ex_Texcoord = geom_Texcoord[0];
	EmitVertex();
	gl_Position = transform * p2;
	ex_Texcoord = geom_Texcoord[1];
	EmitVertex();
	gl_Position = transform * p3;
	ex_Texcoord = geom_Texcoord[2];
	EmitVertex();

	EndPrimitive();
}
