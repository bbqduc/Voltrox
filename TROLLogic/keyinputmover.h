#pragma once

#include <TROLCommon/types.h>
#include "iinputhandler.h"

class KeyInputMover : public IKeyInputHandler
{
    public:
        virtual void handleKeyEvent(int key, int action);
        virtual void update();
        void registerEntity(eid_t e) { entity = e; }
    private:
        eid_t entity;
};
