#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
	friend class Engine;
	friend class Renderer;

	glm::vec3 pos, up, view, right;
	glm::quat orientation;

	void updateVectors();
public:
	void handleMouseInput(float x, float y);
	void handleKeyInput();

	Camera() : pos(0,150,20), up(0,1,0), view(0,0,-1), right(1,0,0) 
	{
		orientation = glm::rotate(orientation, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		updateVectors();
	}

};