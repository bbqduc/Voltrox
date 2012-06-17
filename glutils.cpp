#include "glutils.h"

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif
#include <GL/glfw.h>
#include <GL/gl.h>

#include <iostream>


void checkGLErrors(const char* functionName)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		fprintf(stderr, "%s -- ERROR: %s\n", functionName, gluErrorString(err));
		exit(-1);
	}
}

Model fullScreenQuadModel()
{
	glm::vec3 vertices2[4];
	vertices2[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	vertices2[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
	vertices2[2] = glm::vec3(1.0f, 1.0f, 0.0f);
	vertices2[3] = glm::vec3(1.0f, -1.0f, 0.0f);

	glm::uvec3 polygons2[2];
	polygons2[0] = glm::uvec3(0,1,2);
	polygons2[1] = glm::uvec3(2,3,0);

	return Model(4,2, &vertices2[0], &polygons2[0], GL_TRIANGLES);
}

int init()
{
	if( !glfwInit()) 	
	{
		printf("GLFWINIT FAILED!\n");
		return -1;
	}

	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	//	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(!glfwOpenWindow(1024,768,0,0,0,0,0,0, GLFW_WINDOW))
	{
		printf("Cannot open window!\n");
		glfwTerminate();
		return -1;
	}
#ifdef TROL_USE_OLD_OPENGL
	if(glewInit() != GLEW_OK)
	{
		printf("Glew init failed!\n");
		return -1;
	}
#else
	if(gl3wInit()) 
	{
		printf("Gl3w init failed!\n");
		return -1;
	}
	if(!gl3wIsSupported(3,2))
	{
		printf("opengl 3.2 is not supported\n");
		return -1;
	}
#endif

	checkGLErrors("init");

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	return 0;
}
