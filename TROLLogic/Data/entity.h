#pragma once

#include <glm/glm.hpp>

class Model;

struct Entity
{
	const Model* model;
	glm::vec3 position;

	Entity():model(0) {}
	Entity(const Model* model_, glm::vec3 position_):model(model_), position(position_) {}
};