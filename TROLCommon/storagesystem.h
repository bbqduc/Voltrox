#pragma once
#include <vector>
#include <list>
#include "types.h"
#include "componentstore.h"
#define MAX_SYSTEMS 64

class StorageSystem
{
    public:
        void* addComponent(eid_t entity, ct_t component);
        void* getComponent(eid_t entity, ct_t component);
        void removeComponent(eid_t entity, ct_t component);
        void removeEntity(eid_t entity);
        eid_t createEntity();
        SortedArray<ComponentStore::Index_t>& getComponents(ct_t);

        StorageSystem(size_t maxEntities);
        void addSystem(size_t entrySize) { new (&componentStores[numSystems++]) ComponentStore(entrySize, maxEntities); }
    private:
        const size_t maxEntities;
        ComponentStore componentStores[MAX_SYSTEMS];
        size_t numSystems;
        std::list<eid_t> freelist;
};
