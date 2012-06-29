#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Model;

struct Entity
{
	const Model* model;
	glm::vec3 position;
	glm::vec3 direction;

	glm::quat orientation;

	Entity():model(0) {}
	Entity(const Model* model_, glm::vec3 position_ = glm::vec3(), glm::quat orientation_ = glm::quat()):model(model_), position(position_), orientation(orientation_) {}

	void handleKeyInput(bool* keysDown)
	{
		if(keysDown['W'])
			position += direction * 0.1f;
//		if(keysDown['A'])
		if(keysDown['S'])
			position += direction - 0.1f;
//		if(keysDown['D'])
	}
};