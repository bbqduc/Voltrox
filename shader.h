#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <map>
#include <string>
#include <stdint.h>

#define MAX_UNIFORMS 16

struct Shader
{
	GLuint id;
	GLint uniformLocs[MAX_UNIFORMS];
	uint8_t numUniforms;
	std::map<std::string, GLint> stringLocations;

	bool loadFromFile(const char* vPath, const char* fPath, const char* gPath);
	bool loadFromShaderDir(const char* vPath, const char* fPath, const char* gPath);
	uint8_t storeUniformLoc(const char* name);
	Shader():numUniforms(0) {}

	static const std::string shaderPath;
};