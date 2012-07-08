#pragma once

#include "system.h"
#include "LinearMath/btTransform.h"

const msg_t ADD_PHYSICS_LINK = LAST_BASE_MSG + 1;

class PositionSystem : public System<btTransform*>
{
	public:
	virtual rsp_t handleMessage(Message);
	private:
};

rsp_t PositionSystem::handleMessage(Message msg)
{
	switch(msg.mType)
	{
		case ADD_PHYSICS_LINK:
			btTransform* link = static_cast<btRigidBody*>(GLOBALTHING::getComponent(msg.entity, CT_PHYSICS))->getWorldTransform();
			*addComponent(msg.entity) = link;
		return MSG_DONE;
	}
}