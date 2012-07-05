#pragma once
#include "irender.h"
#include "../TROLUtil/sortedarray.h"
#include "../TROLLogic/explosioninfo.h"
#include <btBulletDynamicsCommon.h>


class MeshExplodeRenderer : public IRenderer
{
	public:
		void render();
		void registerEntity(ExplosionInfo& e) { explosions.insert(&e); }
		void unRegisterEntity(ExplosionInfo& e) { explosions.remove(explosions.search(&e)); }
	private:
		SortedArray<ExplosionInfo*> explosions;
};