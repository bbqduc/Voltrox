#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../../TROLGraphics/Data/model.h"

#include "../inputhandler.h"
#include <memory>
#include <iostream>
														  
struct Entity
{
	static const btQuaternion identityQuat;
	static const btVector3 identityVec3;

	Model& model;
	btDefaultMotionState motionState;
	btRigidBody physicsBody;
	bool collided, exploded;

	private:
	Entity(const Entity&);
	Entity& operator=(const Entity&);

	friend class EntityStorage;
	Entity(Model& model_, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat, float mass=1.0f)
		:
		model(model_),
		motionState(btDefaultMotionState(btTransform(orientation, position))),
		physicsBody(btRigidBody::btRigidBodyConstructionInfo(mass, &motionState, &model_.collisionShape, model_.getInertia(mass))),
		collided(false),
		exploded(false)
	{
		physicsBody.setUserPointer(static_cast<void*>(this));
	}
};
