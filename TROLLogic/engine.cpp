#include "engine.h"
#include "inputhandler.h"
#include <iostream>
#include "../root.h"

#include "../TROLGraphics/Managers/modelmanager.h"
#include "../TROLGraphics/meshrender.h"
#include "../TROLGraphics/meshexplode.h"

void myTickCallback(btDynamicsWorld* world, btScalar timeStep)
{
	Engine* e = static_cast<Engine*> (world->getWorldUserInfo());
	e->physicsCallback(timeStep);
}
void Engine::physicsCallback(btScalar timeStep)
{
	//Assume world->stepSimulation or world->performDiscreteCollisionDetection has been called
	int numManifolds = dynamicsWorld.getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  dynamicsWorld.getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
		if(numContacts)
		{
			Entity* e1 = static_cast<Entity*>(obA->getUserPointer());
			Entity* e2 = static_cast<Entity*>(obA->getUserPointer());
			if(e1 && !e1->collided)
			{
				e1->collided = true;
			}
			if(e2 && !e2->collided)
			{
				e2->collided = true;
			}
		}
	}
}

Engine::Engine()
	:meshRenderer(Root::getSingleton().renderManager.getNewRenderManager<MeshRenderer>()),
	meshExplodeRenderer(Root::getSingleton().renderManager.getNewRenderManager<MeshExplodeRenderer>()),
	broadphase(),
	collisionConfiguration(),
	solver(),
	dispatcher(&collisionConfiguration),
	dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration),
	fireCooldown(0.0f),
	gravity(0,-10,0)
{
	dynamicsWorld.setGravity(gravity);
	dynamicsWorld.setInternalTickCallback(myTickCallback, static_cast<void*>(this));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld.addRigidBody(groundRigidBody);
}

void Engine::addEntity(Entity& e)
{
	simulEntities.insert(&e);
	dynamicsWorld.addRigidBody(&e.physicsBody);
	meshRenderer.registerEntity(e);
}

void Engine::updateGravity(const btVector3& g)
{
	gravity = g;
	dynamicsWorld.setGravity(gravity);

	for(int i = 0; i < simulEntities.size(); ++i)
	{
		simulEntities[i]->physicsBody.activate();
		simulEntities[i]->physicsBody.setGravity(dynamicsWorld.getGravity());
	}
}

void Engine::explodeEntity(Entity& en)
{
	if(en.exploded)
		return;
	en.exploded = true;
	en.physicsBody.setCollisionFlags(btRigidBody::CF_NO_CONTACT_RESPONSE);
	en.physicsBody.setAngularVelocity(btVector3(0,0,0));
	ExplosionInfo* e = new (explosionsPool.alloc()) ExplosionInfo(en, btVector3(0,0,-6), 15.0f);
	explosions.insert(e);
	meshRenderer.unRegisterEntity(en);
	meshExplodeRenderer.registerEntity(*e);
}

void Engine::removeExplosion(ExplosionInfo& e)
{
	simulEntities.remove(simulEntities.search(&e.entity));
	meshExplodeRenderer.unRegisterEntity(e);
	explosionsPool.dealloc(&e);
	explosions.remove(explosions.search(&e));
}

void Engine::fireCube()
{
	btVector3 pos(camera.pos.x, camera.pos.y, camera.pos.z);
	btQuaternion ori(camera.orientation.x, camera.orientation.y, camera.orientation.z, camera.orientation.w);
	btVector3 view(camera.view.x, camera.view.y, camera.view.z);

	Entity* e = Root::getSingleton().entityStorage.addEntity(Root::getSingleton().modelManager.getModel("cube_tex"), pos, ori);
	addEntity(*e);
	e->physicsBody.activate();
	e->physicsBody.applyImpulse(view*100, btVector3(0,0,0));
}

void Engine::tick()
{
	InputHandler& i = Root::getSingleton().inputHandler;

	if(i.isKeyDown('X') && explosions.size() == 0)
		explodeEntity(*simulEntities[0]);

	for(int i = 0; i < simulEntities.size(); ++i)
		if(simulEntities[i]->collided)
			explodeEntity(*simulEntities[i]);

	for(int i = 0; i < explosions.size(); ++i)
		if(explosions[i]->timeElapsed > explosions[i]->TTL)
			removeExplosion(*explosions[i]);
		else
			explosions[i]->timeElapsed += 0.1f;

	dynamicsWorld.stepSimulation(1/60.0f, 10);

	camera.handleMouseInput();
	camera.handleKeyInput();

	if(i.isKeyDown(GLFW_KEY_SPACE))
		for(int i = 0; i < simulEntities.size(); ++i)
		{
			simulEntities[i]->physicsBody.activate();
			simulEntities[i]->physicsBody.applyForce(btVector3(0,20,0), btVector3(0,0,0));
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
		dynamicsWorld.removeRigidBody(&simulEntities[i]->physicsBody);
}

Engine::~Engine()
{
}
