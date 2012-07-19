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
        void attachCamera(eid_t entity) { camera = entity; }
	private:
		eid_t camera;
};
