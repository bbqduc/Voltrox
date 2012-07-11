#pragma once

// Handles the distribution of new entity-ids and deletion of old ones
//
#include "types.h"
#include <list>

class EntitySystem
{
    public:
        EntitySystem();
        eid_t createEntity();
        void removeEntity(eid_t);
    private:
        std::list<eid_t> availables;
};
