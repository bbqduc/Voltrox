#include "inputsystem.h"
#include <TROLCommon/root.h>

#include <GL/glfw.h>
#include <cassert>

bool InputSystem::isKeyDown(int key) 
{ 
	assert(key <= GLFW_KEY_LAST);
	return glfwGetKey(key) == GLFW_PRESS; 
}
void InputSystem::getMousePos(int *x, int *y) 
{ 
	assert(x && y);
	glfwGetMousePos(x,y);
}

void InputSystem::getMousePos(float *x, float *y) 
{ 
	assert(x && y);
	int xi, yi;
	glfwGetMousePos(&xi,&yi);
	*x = -0.5f + xi / (float)Root::openGLWindow.getResX();
	*y = -0.5f + yi / (float)Root::openGLWindow.getResY();
}

void InputSystem::centerMouse()
{
	int x = Root::openGLWindow.getResX();
	int y = Root::openGLWindow.getResY();
	glfwSetMousePos(x/2, y/2);
}

