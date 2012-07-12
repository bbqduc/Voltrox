#include "positionsystem.h"
#include "root.h"

rsp_t PositionSystem::handleMessage(Message msg)
{
	switch(msg.mType)
	{
		case PHYS_ADD_LINK:
			btTransform* link = &static_cast<btRigidBody*>(Root::storageSystem.getComponent(msg.entity, CT_PHYSICS))->getWorldTransform();
			*static_cast<btTransform**>(Root::storageSystem.addComponent(msg.entity, CT_POSITION)) = link;
		return MSG_DONE;
	}
}
