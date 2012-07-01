#include "engine.h"
#include "inputhandler.h"

Engine::Engine()
	:broadphase(new btDbvtBroadphase()),
	collisionConfiguration(new btDefaultCollisionConfiguration()),
	solver(new btSequentialImpulseConstraintSolver()),
	dispatcher(new btCollisionDispatcher(collisionConfiguration)),
	dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration))
{
	dynamicsWorld->setGravity(btVector3(0,-10,0));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo
	groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
}

void Engine::tick()
{
	dynamicsWorld->stepSimulation(1/60.0f, 10);
	int x, y;
	InputHandler::getMousePos(&x,&y);
	float fx = x / 1024.0f-0.5f, fy = y / 768.0f-0.5f;
	camera->handleMouseInput(fx,fy);
	glfwSetMousePos(1024/2, 768/2);
	camera->handleKeyInput();

	entities[0].handleKeyInput();
}
