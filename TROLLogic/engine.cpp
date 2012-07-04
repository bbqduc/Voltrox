#include "engine.h"
#include "inputhandler.h"
#include <iostream>
#include "../root.h"

#include "../TROLGraphics/Managers/modelmanager.h"

	Engine::Engine()
:broadphase(),
	collisionConfiguration(),
	solver(),
	dispatcher(&collisionConfiguration),
	dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration),
	fireCooldown(0.0f),
	gravity(0,-10,0)
{
	dynamicsWorld.setGravity(gravity);

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld.addRigidBody(groundRigidBody);
}

void Engine::updateGravity(const btVector3& g)
{
	gravity = g;
	dynamicsWorld.setGravity(gravity);

	for(int i = 0; i < simulEntities.size(); ++i)
	{
		simulEntities[i]->physicsBody->activate();
		simulEntities[i]->physicsBody->setGravity(dynamicsWorld.getGravity());
	}
}

void Engine::fireCube()
{
	Camera& camera = Root::getSingleton().renderer.getCamera();
	btVector3 pos(camera.pos.x, camera.pos.y, camera.pos.z);
	btQuaternion ori(camera.orientation.x, camera.orientation.y, camera.orientation.z, camera.orientation.w);
	btVector3 view(camera.view.x, camera.view.y, camera.view.z);

	Entity* e = Root::getSingleton().entityStorage.addEntity(Root::getSingleton().modelManager.getModel("cube_tex"), pos, ori);
	addEntity(*e);
	e->physicsBody->activate();
	e->physicsBody->applyImpulse(view*100, btVector3(0,0,0));
}

void Engine::tick()
{
	InputHandler& i = Root::getSingleton().inputHandler;

	if(!Renderer::explodeAll)
		dynamicsWorld.stepSimulation(1/60.0f, 10);
	if(i.isKeyDown('X'))
		Renderer::explodeAll = true;

	Camera& camera = Root::getSingleton().renderer.getCamera();
	camera.handleMouseInput();
	camera.handleKeyInput();

	if(i.isKeyDown(GLFW_KEY_SPACE))
		for(int i = 0; i < simulEntities.size(); ++i)
		{
			simulEntities[i]->physicsBody->activate();
			simulEntities[i]->physicsBody->applyForce(btVector3(0,20,0), btVector3(0,0,0));
		}

	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && fireCooldown <= 0.0f)
	{
		fireCooldown = 5.0f;
		fireCube();
	}


	if(i.isKeyDown('G') && gravity != btVector3(0,0,0))
		updateGravity(btVector3(0,0,0));

	if(fireCooldown > 0.0f)
		fireCooldown -= 0.1f;
}

void Engine::destroy()
{
	for(int i = 0; i < simulEntities.size(); ++i)
		dynamicsWorld.removeRigidBody(simulEntities[i]->physicsBody);
}

Engine::~Engine()
{
}
