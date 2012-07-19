#include "storagesystem.h"
#include <cassert>
#include <iostream>

StorageSystem::StorageSystem(size_t maxEntities_)
    :maxEntities(maxEntities_),
    numSystems(0)
{
    for(eid_t i = 1; i <= maxEntities; ++i)
        freelist.push_back(i);
}

void* StorageSystem::addComponent(eid_t entity, ct_t component)
{
    assert(numSystems >= component);
    return componentStores[component].addComponent(entity);
}

void* StorageSystem::getComponent(eid_t entity, ct_t component)
{
    assert(numSystems >= component);
    return componentStores[component].getComponent(entity);
}

void StorageSystem::removeComponent(eid_t entity, ct_t component)
{
    assert(numSystems >= component);
    componentStores[component].removeComponent(entity);
}

void StorageSystem::removeEntity(eid_t entity)
{
    // TODO : don't think sortedarray is capable of telling something wasn't
    // found, so this doesn't remove it from components
    freelist.push_front(entity);
}

SortedArray<ComponentStore::Index_t>& StorageSystem::getComponents(ct_t component)
{
    assert(numSystems >= component);
    return componentStores[component].getComponents();
}

eid_t StorageSystem::createEntity()
{
    eid_t ret = freelist.front();
    freelist.pop_front();
    return ret;
}
