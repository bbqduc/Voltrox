#include "entitysystem.h"

EntitySystem::EntitySystem()
{
    for(int i = 1; i <= MAX_ENTITIES; ++i)
        availables.push_back(i);
}

eid_t EntitySystem::createEntity()
{
    eid_t ret = availables.front();
    availables.pop_front();

    return ret;
}

void EntitySystem::removeEntity(eid_t e)
{
    availables.push_front(e);
}
