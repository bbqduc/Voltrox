#include "inputsystem.h"
#include <TROLCommon/root.h>

#include <cassert>

InputSystem* InputSystem::isystem = 0;

TROLLOERROR InputSystem::init() 
{ 
    InputSystem::isystem = this; 
    glfwSetKeyCallback(InputSystem::keyCallback); 
    return TROLLO_OK;
}

void GLFWCALL InputSystem::keyCallback(int key, int action)
{
    for(auto i = isystem->keyHandlers.begin(); i != isystem->keyHandlers.end(); ++i)
        (*i)->handleKeyEvent(key,action);
}

void InputSystem::update()
{
    float x, y;
    getMousePos(&x,&y);
    for(auto i = isystem->mouseHandlers.begin(); i != isystem->mouseHandlers.end(); ++i)
        (*i)->handleMouseMove(x,y);
    for(auto i = isystem->keyHandlers.begin(); i != isystem->keyHandlers.end(); ++i)
        (*i)->update();
}

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

