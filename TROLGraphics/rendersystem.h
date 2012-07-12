#pragma once

#include <TROLCommon/system.h>
#include <TROLCommon/componentstore.h>
#include "Data/model.h"

class RenderSystem : public ISystem
{
	public:
		void render();
        RenderSystem():ISystem(CTFlags::RENDERABLE) {}
        virtual rsp_t handleMessage(Message m) { return MSG_IGNORED; }
        ComponentStore<Model*> store;
	private:
		eid_t camera;
};
