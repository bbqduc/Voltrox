#include "keyinputmover.h"
#include <TROLCommon/root.h>

void KeyInputMover::update()
{
    float t = 0.0f;
    if(glfwGetKey('W') == GLFW_PRESS)
    {
        float force = 20.0f;
        Message msg;
        msg.data = &force;
        msg.mType = PHYS_THRUSTERS;
        msg.entity = entity;
        Root::broadcastMessage(msg, CTFlags::PHYSICS);
    }

    if(glfwGetKey('S') == GLFW_PRESS )
    {
        Message msg;
        msg.mType = PHYS_BRAKES;
        msg.entity = entity;
        Root::broadcastMessage(msg, CTFlags::PHYSICS);
    }
    if(glfwGetKey('Q') == GLFW_PRESS)
        t += 10.0f;
    if(glfwGetKey('E') == GLFW_PRESS)
        t += -10.0f;
    if(t)
    {
        btVector3 torque(0.0f, 0.0f, t);

        Message msg;
        msg.entity = entity;
        msg.mType = PHYS_ROTATE;
        msg.data = &torque;
        Root::broadcastMessage(msg, CTFlags::PHYSICS);
    }
}

void KeyInputMover::handleKeyEvent(int key, int action)
{
}
