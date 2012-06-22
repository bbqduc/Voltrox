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
		fprintf(stderr, "%s -- ERROR: %s\n", functionName, gluErrorString(err));
		exit(-1);
	}
}