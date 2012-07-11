#pragma once

#include "system.h"
#include <LinearMath/btTransform.h>

class PositionSystem : public System<btTransform*>
{
	public:
	virtual rsp_t handleMessage(Message);
    PositionSystem() : System<btTransform*>(CTFlags::POSITION) {}
	private:
};

