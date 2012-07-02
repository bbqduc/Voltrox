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
	~Engine();

	Camera* camera;
	ModelManager* modelManager;

	void tick();

	void addEntity(const Model& model, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat) 
	{ 
		entities.push_back(Entity(&model, position, orientation)); 
		dynamicsWorld->addRigidBody(entities[entities.size()-1].physicsBody);
	}

	void setActive(Entity& entity) { activeInputEntity = &entity; }
	const btAlignedObjectArray<Entity>& getEntities() const {return entities;}

};
