#pragma once

#include "../system.h"
#include "../root.h"

class RenderSystem : public System<Model*>
{
	public:
		void render();
	private:
		eid_t camera;
};