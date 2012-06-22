#pragma once

#include <glm/glm.hpp>
#include "model.h"

template <typename T>
struct Entity
{
	const Model<T>* model;
	glm::vec3 position;

	Entity():model(0) {}
	Entity(const Model<T>* model_, glm::vec3 position_):model(model_), position(position_) {}
};