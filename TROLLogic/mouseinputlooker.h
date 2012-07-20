#pragma once

#include <TROLCommon/types.h>
#include "iinputhandler.h"

class MouseInputLooker : public IMouseInputHandler
{
    public:
        virtual void handleMouseMove(float x, float y);
        virtual void handleMouseClick(int key, int action) {}
        void registerEntity(eid_t e) { entity = e; }
    private:
        eid_t entity;
};
