#pragma once

#include <glm/glm.hpp>

class Camera
{
	glm::vec3 pos, up, view;
	float angleY, angleX;
	glm::quat orientation;

	public:

	void handleMouseInput()
	{
		int x, y;
		glfwGetMousePos(&x,&y);
		//TROLO
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
	
};