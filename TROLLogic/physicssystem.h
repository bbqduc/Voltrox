#pragma once

#include <TROLCommon/system.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


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

private:
	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	btVector3 gravity;

};
