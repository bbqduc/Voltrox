#pragma once

#include <TROLCommon/system.h>
#include <TROLCommon/componentstore.h>
#include <LinearMath/btTransform.h>

class PositionSystem : public ISystem
{
    public:
        virtual rsp_t handleMessage(Message);
        PositionSystem() : ISystem(CTFlags::POSITION) {}
        ComponentStore<btTransform*> store;
};

