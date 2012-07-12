#pragma once

#include <TROLCommon/system.h>
#include <TROLCommon/componentstore.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

const msg_t PHYS_THRUSTERS = LAST_BASE_MSG + 1;
const msg_t PHYS_SET_COLLISION_FLAGS= LAST_BASE_MSG + 2;

struct PhysCreateMsgData{
		btRigidBody::btRigidBodyConstructionInfo ci;
		btTransform t;
        PhysCreateMsgData():ci(0, NULL, NULL, btVector3(0,0,0)) {}
};

class PhysicsSystem : public ISystem
{
public:
	virtual rsp_t handleMessage(Message msg);
	PhysicsSystem();
	void tick();

    ComponentStore<btRigidBody> store;

private:
	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	btVector3 gravity;

};
