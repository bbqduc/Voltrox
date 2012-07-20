#include "mouseinputlooker.h"
#include <TROLCommon/root.h>

void MouseInputLooker::handleMouseMove(float x, float y)
{
    Root::inputSystem.centerMouse();
    float angleY = -75.0f * x;
    float angleX = 75.0f * y;

    btVector3 torqueX(angleX, 0.0f, 0.0f);
    btVector3 torqueY(0.0f, angleY, 0.0f);

    Message msg;
    msg.entity = entity;
    msg.data = &torqueX;

    msg.mType = PHYS_BRAKES;
    Root::broadcastMessage(msg, CTFlags::PHYSICS);
    msg.mType = PHYS_ROTATE;
    Root::broadcastMessage(msg, CTFlags::PHYSICS);
    msg.data = &torqueY;
    Root::broadcastMessage(msg, CTFlags::PHYSICS);
}
