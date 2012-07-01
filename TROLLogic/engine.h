#pragma once

#include "Data/entity.h"
#include "../TROLGraphics/camera.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

class Engine 
{
	btAlignedObjectArray<Entity> entities;
	Entity* activeInputEntity; /// TODO : UNSAFE

	/// PHYSICS
	btDbvtBroadphase* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;


public:
	Engine();

	Camera* camera;
	void tick();

	void addEntity(const Model& model, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat) 
	{ 
		entities.push_back(Entity(&model, position, orientation)); 
	}
	void addPhysics()
	{
		for(int i = 0; i < entities.size(); ++i)
			dynamicsWorld->addRigidBody(entities[i].physicsBody);
	}
	void setActive(Entity& entity) { activeInputEntity = &entity; }
	const btAlignedObjectArray<Entity>& getEntities() const {return entities;}

};
