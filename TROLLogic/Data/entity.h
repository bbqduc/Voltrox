#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../../TROLGraphics/Data/model.h"

#include "../inputhandler.h"

struct Entity
{
	static const btQuaternion identityQuat;
	static const btVector3 identityVec3;

	const Model* model;
	btVector3 position;
	btQuaternion orientation;

	btDefaultMotionState* motionState;
	btRigidBody* physicsBody;

	Entity():model(0), motionState(0), physicsBody(0)  {}
	Entity(const Model* model_, const btVector3& position_ = Entity::identityVec3, const btQuaternion& orientation_ = Entity::identityQuat)
		:model(model_),
		position(position_),
		orientation(orientation_),
		motionState(new btDefaultMotionState(btTransform(orientation, position))),
		physicsBody(0)
	{
		btScalar mass = 1.0f;
		btVector3 inertia(0,0,0);
		model->collisionShape->calculateLocalInertia(mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, model->collisionShape, inertia);
		physicsBody = new btRigidBody(rigidBodyCI);
	}

	void handleKeyInput()
	{
		if(InputHandler::isKeyDown(GLFW_KEY_SPACE))
			physicsBody->applyForce(btVector3(0,50,0), btVector3(0,0,0));
/*		if(keysDown['W'])
			position += direction * 0.1f;
		if(keysDown['S'])
			position += direction - 0.1f;*/
	}
};