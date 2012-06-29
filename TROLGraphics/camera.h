#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
	friend class Renderer;
	glm::vec3 pos, up, view, right;
	glm::quat orientation;

	public:
	void handleMouseInput(float x, float y);
	void handleKeyInput();

	Camera() : pos(0,0,0), up(0,1,0), view(0,0,-1), right(1,0,0) {}

};