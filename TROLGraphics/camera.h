#pragma once

#include <glm/glm.hpp>

class Camera
{
	glm::vec3 pos, up, view;
	float angleY, angleX;
	glm::quat orientation;

	public:

	void handleMouseInput(float x, float y)
	{
		angleY += mouseSens * (1024/2 - x);
		angleX += mouseSens * (768/2 - y);
		camView = glm::vec3(cos(angleX) * sin(angleY),
			sin(angleX),
			cos(angleX) * cos(angleY));
		glm::vec3 right = glm::vec3(sin(angleY - 3.14f/2.0f),
			0,
			cos(angleY - 3.14f/2.0f));
		camUp = glm::cross( right, camView );

	}

};
