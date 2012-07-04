#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../../TROLGraphics/Data/model.h"

#include "../inputhandler.h"

struct Entity
{
	static const btQuaternion identityQuat;
	static const btVector3 identityVec3;

	Model* model;
	btDefaultMotionState motionState;
	btRigidBody physicsBody;


	private:
	Entity(const Entity&);
	Entity& operator=(const Entity&);

	friend class EntityStorage;
	Entity(Model& model_, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat, float mass=1.0f)
		:model(&model_),
		motionState(btTransform(orientation, position)),
		physicsBody(btRigidBody::btRigidBodyConstructionInfo(mass, &motionState, &model->collisionShape, model->getInertia(mass)))
	{}
};
