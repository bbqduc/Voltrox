#pragma once

#include "../TROLUtil/sortedarray.h"
#include "../TROLUtil/memorypool.h"
#include "explosioninfo.h"
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

	const Camera& getCamera() { return camera; }
private:
	friend class Root;
	Engine();

	void updateGravity(const btVector3& g);
	void fireCube();

	/// VISUALS
	Camera camera;
	MeshRenderer& meshRenderer;
	MeshExplodeRenderer& meshExplodeRenderer;
	MemoryPool<ExplosionInfo> explosionsPool;

	/// PHYSICS
	btDbvtBroadphase broadphase;
	btDefaultCollisionConfiguration collisionConfiguration;
	btSequentialImpulseConstraintSolver solver;
	btCollisionDispatcher dispatcher;
	btDiscreteDynamicsWorld dynamicsWorld;

	SortedArray<Entity*> simulEntities;
	SortedArray<ExplosionInfo*> explosions;

	float fireCooldown;
	btVector3 gravity;
};
