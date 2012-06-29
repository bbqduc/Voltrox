#include "engine.h"
#include "inputhandler.h"

void Engine::tick()
{
	int x, y;
	InputHandler::getMousePos(&x,&y);
	float fx = x / 1024.0f-0.5f, fy = y / 768.0f-0.5f;
	camera->handleMouseInput(fx,fy);
	glfwSetMousePos(1024/2, 768/2);
	camera->handleKeyInput();
}