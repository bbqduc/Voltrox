#include "inputhandler.h"
#include "../root.h"

#include <GL/glfw.h>
#include <cassert>

bool InputHandler::isKeyDown(int key) 
{ 
	assert(key <= GLFW_KEY_LAST);
	return glfwGetKey(key) == GLFW_PRESS; 
}
void InputHandler::getMousePos(int *x, int *y) 
{ 
	assert(x && y);
	glfwGetMousePos(x,y);
}

void InputHandler::getMousePos(float *x, float *y) 
{ 
	assert(x && y);
	int xi, yi;
	glfwGetMousePos(&xi,&yi);
	*x = -0.5f + xi / (float)Root::getSingleton().renderManager.getResX();
	*y = -0.5f + yi / (float)Root::getSingleton().renderManager.getResY();
}

void InputHandler::centerMouse()
{
	int x = Root::getSingleton().renderManager.getResX();
	int y = Root::getSingleton().renderManager.getResY();
	glfwSetMousePos(x/2, y/2);
}

