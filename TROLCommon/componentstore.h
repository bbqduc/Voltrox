#pragma once
#include <TROLUtil/memorypool.h>
#include <TROLUtil/sortedarray.h>
#include <stdint.h>
#include "types.h"

class ComponentStore
{
    public:
    struct Index_t
    {
        eid_t entity;
        void* component;
        bool operator<(const Index_t& a) const { return entity < a.entity; }
        bool operator<=(const Index_t& a) const { return entity <= a.entity; }
        bool operator==(const Index_t& a) const { return entity == a.entity; }
        bool operator!=(const Index_t& a) const { return entity != a.entity; }
    };

    SortedArray<Index_t>& getComponents() { return index; }
    void* addComponent(eid_t entity);
    void* getComponent(eid_t);
    void removeComponent(eid_t entity);

    ComponentStore(size_t entrySize=8, size_t maxEntries=1)
                :mpool(entrySize, maxEntries),
                index(maxEntries)
                {}

    protected:
    MemoryPool mpool;
    SortedArray<Index_t> index;
};

void* ComponentStore::getComponent(eid_t entity)
{
    Index_t t = { entity, 0 };
    int i = index.search(t);
    Index_t ret = index[i];
    assert(ret.entity == entity && ret.component);

    return ret.component;
}

void* ComponentStore::addComponent(eid_t entity)
{
    // TODO : need some asserts
    void* ret = mpool.alloc();
    Index_t temp = {entity, ret};
    index.insert(temp);
    return ret;
}

void ComponentStore::removeComponent(eid_t entity)
{
    // TODO : some asserts
    Index_t search = {entity, 0};
    int i = index.search(search);
    Index_t temp = index[i];
    mpool.dealloc(temp.component);
    index.remove(i);
}
