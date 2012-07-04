#include "camera.h"
#include "../root.h"

#include "../TROLLogic/inputhandler.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Camera::handleMouseInput()
{
	float x, y;
	Root::getSingleton().inputHandler.getMousePos(&x,&y);
	Root::getSingleton().inputHandler.centerMouse(); // TODO : this might belong somewhere else

	float angleY = -75.0f * x;
	float angleX = -75.0f * y;
	orientation = glm::rotate(orientation, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	orientation = glm::rotate(orientation, angleX, glm::vec3(1.0f, 0.0f, 0.0f));

	updateVectors();
}

void Camera::handleKeyInput()
{
	InputHandler& i = Root::getSingleton().inputHandler;
		if(i.isKeyDown('W'))
			pos += view * 5.0f;
		if(i.isKeyDown('S'))
			pos -= view * 5.0f;
		if(i.isKeyDown('A'))
			pos -= right * 5.0f;
		if(i.isKeyDown('D'))
			pos += right * 5.0f;
		if(i.isKeyDown('Q'))
		{
			orientation = glm::rotate(orientation, 1.0f, glm::vec3(0.0f,0.0f,1.0f));
			updateVectors();
		}
		if(i.isKeyDown('E'))
		{
			orientation = glm::rotate(orientation, -1.0f, glm::vec3(0.0f,0.0f,1.0f));
			updateVectors();
		}
}

void Camera::updateVectors()
{
	view = glm::rotate(orientation, glm::vec3(0.0f,0.0f,-1.0f));
	up = glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	right = glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f));
}
