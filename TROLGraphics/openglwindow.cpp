#include "openglwindow.h"
#include <GL3/gl3w.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "glutils.h"

TROLLOERROR OpenGLWindow::init(int resX, int resY)
{
	this->resX = resX;
	this->resY = resY;
	this->perspective = glm::perspective(45.0f, (float)resX/(float)resY, 1.0f, 10000.0f);

	return initGL();
}

TROLLOERROR OpenGLWindow::initGL()
{
	if( !glfwInit()) 	
		return TROLLO_INIT_FAILURE;

#ifndef TROL_USE_OLD_OPENGL // Request core profile if possible
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	if(!glfwOpenWindow(resX,resY,8,8,8,8,24,0, GLFW_WINDOW))
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#ifdef TROL_USE_OLD_OPENGL
	if(glewInit() != GLEW_OK || !glewIsSupported("GL_ARB_geometry_shader4"))
	{
		std::cerr << "GEOMETRY SHADER NOT SUPPORTED\n";
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#else
	if(gl3wInit()) 
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
	if(!gl3wIsSupported(3,3))
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#endif

	checkGLErrors("init");

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << "\nGLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << "\nRenderer : " << glGetString(GL_RENDERER) << "\n\n";

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);	  

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetMousePos(resX / 2, resY / 2);
	glfwDisable(GLFW_MOUSE_CURSOR);

	checkGLErrors("post_init");

	return TROLLO_OK;
}
