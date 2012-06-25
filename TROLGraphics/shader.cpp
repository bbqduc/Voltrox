#include "shader.h"
#include "glutils.h"

#include <cstdlib>
#include <cstdio>

uint8_t Shader::storeUniformLoc(const char* name)
{
	uniformLocs[numUniforms] = glGetUniformLocation(id, name);	
	stringLocations[name] = uniformLocs[numUniforms];
	return numUniforms++;
}