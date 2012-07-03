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
	dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
	dynamicsWorld.setGravity(btVector3(0,-10,0));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo
	groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld.addRigidBody(groundRigidBody);
}

void Engine::tick()
{
	static bool mouseDown = false;
	static bool gravityOn = true;
	Camera& camera = Root::getSingleton().renderer.getCamera();

	if(!Renderer::explodeAll)
		dynamicsWorld.stepSimulation(1/60.0f, 10);
	if(InputHandler::isKeyDown('X'))
		Renderer::explodeAll = true;
	int x, y;
	Root::getSingleton().inputHandler.getMousePos(&x,&y);
	float fx = x / 1024.0f-0.5f, fy = y / 768.0f-0.5f;
	camera.handleMouseInput(fx,fy);
	glfwSetMousePos(1024/2, 768/2);
	camera.handleKeyInput();

	if(InputHandler::isKeyDown(GLFW_KEY_SPACE))
		for(int i = 0; i < entities.size(); ++i)
		{
			entities[i].physicsBody->activate();
			entities[i].physicsBody->applyForce(btVector3(0,20,0), btVector3(0,0,0));
		}

	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) != GLFW_PRESS)
		mouseDown = false;
	if(!mouseDown && glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		mouseDown = true;
		btVector3 pos(camera.pos.x, camera.pos.y, camera.pos.z);
		btQuaternion ori(camera.orientation.x, camera.orientation.y, camera.orientation.z, camera.orientation.w);
		btVector3 view(camera.view.x, camera.view.y, camera.view.z);

		addEntity(Root::getSingleton().modelManager.getModel("cube_tex"), pos, ori);
		entities[entities.size()-1].physicsBody->activate();
		entities[entities.size()-1].physicsBody->applyImpulse(view*100, btVector3(0,0,0));
	}


	if(gravityOn && InputHandler::isKeyDown('G'))
	{
		gravityOn = false;
		dynamicsWorld.setGravity(btVector3(0,0,0));

		for(int i = 0; i < entities.size(); ++i)
		{
			entities[i].physicsBody->activate();
			entities[i].physicsBody->setGravity(dynamicsWorld.getGravity());
		}
	}
}

void Engine::destroy()
{
	for(int i = 0; i < entities.size(); ++i)
	{
		dynamicsWorld.removeRigidBody(entities[i].physicsBody);
		entities[i].destroy();
	}
}

Engine::~Engine()
{
}
