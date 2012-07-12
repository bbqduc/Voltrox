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
