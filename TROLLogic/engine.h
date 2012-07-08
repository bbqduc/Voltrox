#pragma once

#include "../system.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

const msg_t PHYS_TICK = LAST_BASE_MSG + 1;
const msg_t PHYS_THRUSTERS = LAST_BASE_MSG + 2;
const msg_t PHYS_SET_COLLISION_FLAGS= LAST_BASE_MSG + 3;

class PhysicsSystem : public System<btRigidBody>
{
public:
	virtual rsp_t handleMessage(Message msg);
	PhysicsSystem();
private:
	Engine(const );
	void tick();

	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	btVector3 gravity;
};