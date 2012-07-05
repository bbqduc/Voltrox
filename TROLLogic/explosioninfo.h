#pragma once
#include <btBulletDynamicsCommon.h>

class Entity;

struct ExplosionInfo
{
	btVector3 localPosition;
	Entity& entity;
	float timeElapsed, TTL;
	ExplosionInfo(Entity& e, btVector3& p, float TTL_)
		:
		localPosition(p),
		entity(e),
		timeElapsed(0.0f),
		TTL(TTL_)
		{}
};