#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Model;

struct Entity
{
	const Model* model;
	glm::vec3 position;
	glm::quat orientation;

	Entity():model(0) {}
	Entity(const Model* model_, glm::vec3 position_ = glm::vec3(), glm::quat orientation_ = glm::quat()):model(model_), position(position_), orientation(orientation_) {}
};