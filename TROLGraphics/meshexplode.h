#pragma once
#include "../TROLUtil/sortedarray.h"
#include <btBulletDynamicsCommon.h>

class Entity;

struct ExplosionInfo
{
	btVector3 localPosition;
	Entity& entity;
	float timeElapsed, TTL;
};

class MeshExplodeRender
{
	public:
		void render();
		void registerEntity(ExplosionInfo& e) { explosions.insert(&e); }
		void unRegisterEntity(ExplosionInfo& e) { explosions.remove(explosions.search(&e)); }
	private:
		SortedArray<ExplosionInfo*> explosions;
};