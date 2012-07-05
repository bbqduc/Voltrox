#pragma once

#include "Data/entity.h"
#include "../TROLGraphics/camera.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <vector>

class MeshRenderer;
class MeshExplodeRenderer;

class Engine 
{
public:
	~Engine();

	void destroy();
	void tick();

	void addEntity(Entity& e);

	const std::vector<Entity*>& getEntities() const {return simulEntities;}
	const Camera& getCamera() { return camera; }
private:
	friend class Root;
	Engine();

	void updateGravity(const btVector3& g);
	void fireCube();

	/// VISUALS
	Camera camera;
	MeshRenderer& meshRenderer;
	MeshExplodeRenderer* meshExplodeRenderer;

	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	std::vector<Entity*> simulEntities;
	std::vector<Entity*> explodingEntities;

	float fireCooldown;
	btVector3 gravity;
};
