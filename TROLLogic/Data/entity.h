#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../../TROLGraphics/Data/model.h"

#include "../inputhandler.h"
#include <memory>
#include <iostream>
														  
struct __declspec(align(16)) Entity
{
	static const btQuaternion identityQuat;
	static const btVector3 identityVec3;

	Model& model;
	btDefaultMotionState motionState;
	char b[4];
	btRigidBody* physicsBody;

	private:
	Entity(const Entity&);
	Entity& operator=(const Entity&);
	char __declspec(align(16)) a[sizeof(btRigidBody)];

	friend class EntityStorage;
	Entity(Model& model_, const btVector3& position = Entity::identityVec3, const btQuaternion& orientation = Entity::identityQuat, float mass=1.0f)
		:
		model(model_),
		motionState(btDefaultMotionState(btTransform(orientation, position))),
		physicsBody(new (a) btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass, &motionState, &model_.collisionShape, model_.getInertia(mass))))
	{
	}
};
