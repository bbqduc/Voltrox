#include "glutils.h"

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif
#include <GL/glfw.h>
#include <GL/gl.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>

void checkGLErrors(const char* functionName)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cerr << functionName << " -- OPENGL ERROR : " << gluErrorString(err) << '\n';
		exit(-1);
	}
}

std::string TROLLOErrorString(TROLLOERROR e)
{
	switch(e)
	{
		case TROLLO_OK:
			return std::string("No error");
		case TROLLO_FILE_NOT_FOUND:
			return std::string("File not found");
		case TROLLO_INVALID_FILE_FORMAT:
			return std::string("Invalid file format");
		case TROLLO_INIT_FAILURE:
			return std::string("System init failure");
		default:
			return std::string("Unknown error code");
	}
}
