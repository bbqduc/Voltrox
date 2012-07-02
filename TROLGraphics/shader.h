#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include <map>
#include <string>
#include <stdint.h>

#define MAX_UNIFORMS 16

typedef int ShaderHandle;

struct Shader
{
	GLuint id;
	GLint uniformLocs[MAX_UNIFORMS];
	uint8_t numUniforms;
	std::map<std::string, GLint> stringLocations;

	uint8_t storeUniformLoc(const char* name);
	Shader():numUniforms(0) {}
};