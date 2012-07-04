#pragma once

#include "Data/entity.h"
#include "../TROLGraphics/camera.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <vector>

class Engine 
{
public:
	~Engine();

	void destroy();
	void tick();

	void addEntity(Entity& e)
	{ 
		simulEntities.push_back(&e);
		dynamicsWorld.addRigidBody(e.physicsBody);
	}

	const std::vector<Entity*>& getEntities() const {return simulEntities;}
private:
	friend class Root;
	Engine();

	void updateGravity(btVector3& g);
	void fireCube();

	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	std::vector<Entity*> simulEntities;
	std::vector<Entity*> explodingEntities;

	float fireCooldown;
	btVector3 gravity;
};
