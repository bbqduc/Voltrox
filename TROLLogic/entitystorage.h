#pragma once

#include "../TROLUtil/memorypool.h"
#include "Data/entity.h"

class EntityStorage
{
	public:
		Entity* addEntity(Model& model, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat)
		{
			Entity* e = new (entities.alloc()) Entity(model, position, orientation);
			return e;
		}
		void removeEntity(Entity* e) { entities.dealloc(e); }

	private:
		MemoryPool<Entity> entities;
};
