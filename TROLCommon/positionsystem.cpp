#include "positionsystem.h"
#include "root.h"

rsp_t PositionSystem::handleMessage(Message msg)
{
	switch(msg.mType)
	{
		case PHYS_ADD_LINK:
			btTransform* link = &Root::physicsSystem.getComponent(msg.entity).getWorldTransform();
			*addComponent(msg.entity) = link;
		return MSG_DONE;
	}
}
