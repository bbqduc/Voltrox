#pragma once

#include <TROLCommon/system.h>
#include "Data/model.h"

class RenderSystem : public System<Model*>
{
	public:
		void render();
        RenderSystem():System<Model*>(CTFlags::RENDERABLE) {}
        virtual rsp_t handleMessage(Message m) { return MSG_IGNORED; }
	private:
		eid_t camera;
};
