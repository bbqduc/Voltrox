#pragma once

#include <vector>
#include "Data/entity.h"
#include "../TROLGraphics/camera.h"

class Engine 
{
	std::vector<Entity> entities;
	Entity* activeInputEntity; /// TODO : UNSAFE

	public:
	Camera* camera;
	void tick();

	void addEntity(Entity& entity) { entities.push_back(entity); }
	void setActive(Entity& entity) { activeInputEntity = &entity; }
	const std::vector<Entity>& getEntities() const {return entities;}
};