#pragma once
#include "irender.h"
#include "../TROLUtil/sortedarray.h"

class Entity;

class MeshRenderer : public IRenderer
{
	public:
		virtual void render();
		void registerEntity(Entity& e) { entities.insert(&e); }
		void unRegisterEntity(Entity& e) { entities.remove(entities.search(&e)); }
	private:
		SortedArray<Entity*> entities;
};