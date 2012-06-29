#pragma once

struct Engine 
{
	bool consoleActive;
	Console* activeConsole;
	Camera camera;

	struct { float mouseSens; } inputSettings;

	//	 int oldMouseX, oldMouseY;
	void handleMouseInput()
	{
		int x, y;
		glfwGetMousePos(&x,&y);
		/*float dx = (x - oldMouseX)*mouseSens;
		float dy = (y - oldMouseY)*mouseSens;*/
		glfwSetMousePos(1024/2,768/2);
		angleY += mouseSens * (1024/2 - x);
		angleX += mouseSens * (768/2 - y);
		camView = glm::vec3(cos(angleX) * sin(angleY),
			sin(angleX),
			cos(angleX) * cos(angleY));
		glm::vec3 right = glm::vec3(sin(angleY - 3.14f/2.0f),
			0,
			cos(angleY - 3.14f/2.0f));
		camUp = glm::cross( right, camView );

		/*		oldMouseX = 0;//x;*/
		//		oldMouseY = 0;//y;
	}

	void moveCamera(int key, int action)
	{
		if(action == GLFW_PRESS)
		{
			if(key == 'W')
				camMove = camView;
			if(key == 'S')
				camMove = -1.0f * camView;
			/*			if(key == GLFW_KEY_S)
			if(key == GLFW_KEY_D)*/
		}
		if(action == GLFW_RELEASE)
		{
			if(key == 'W')
				camMove = glm::vec3();
			if(key == 'S')
				camMove = glm::vec3();
			/*			if(key == GLFW_KEY_S)
			if(key == GLFW_KEY_D)*/
		}
	}

	void GLFWCALL handleKeyEvent(int key, int action) { 
		if(consoleActive)
			activeConsole->handleKeyEvent(key, action); 
		else
			moveCamera(key, action);
	}
};

bool Engine::consoleActive = false;
Console* Engine::activeConsole = 0;
const float Engine::mouseSens = 0.0005f;
float Engine::angleY = 3.14f;
float Engine::angleX = 0.0f;

glm::vec3 Engine::camUp = glm::vec3(0,1,0);
glm::vec3 Engine::camView = glm::vec3(0,0,-1);
glm::vec3 Engine::camPos = glm::vec3();
glm::vec3 Engine::camMove = glm::vec3();