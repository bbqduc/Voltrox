#pragma once
#include <TROLUtil/memorypool.h>
#include <TROLUtil/sortedarray.h>
#include <stdint.h>
#include "types.h"

template <typename T>
class ComponentStore
{
    public:
    struct Index_t
    {
        eid_t entity;
        T* component;
        bool operator<(const Index_t& a) const { return entity < a.entity; }
        bool operator<=(const Index_t& a) const { return entity <= a.entity; }
        bool operator==(const Index_t& a) const { return entity == a.entity; }
        bool operator!=(const Index_t& a) const { return entity != a.entity; }
    };

    SortedArray<Index_t>& getComponents() { return index; }
    T* addComponent(eid_t entity);
    T& getComponent(eid_t);
    void removeComponent(eid_t entity);

    protected:
    MemoryPool<T> mpool;
    SortedArray<Index_t> index;
};

    template <typename T>
T& ComponentStore<T>::getComponent(eid_t entity)
{
    Index_t t = { entity, 0 };
    int i = index.search(t);
    Index_t ret = index[i];
    assert(ret.entity == entity && ret.component);

    return *ret.component;
}

    template <typename T>
T* ComponentStore<T>::addComponent(eid_t entity)
{
    // TODO : need some asserts
    T* ret = static_cast<T*>(mpool.alloc());
    Index_t temp = {entity, ret};
    index.insert(temp);
    return ret;
}

    template <typename T>
void ComponentStore<T>::removeComponent(eid_t entity)
{
    // TODO : some asserts
    Index_t search = {entity, 0};
    int i = index.search(search);
    Index_t temp = index[i];
    mpool.dealloc(temp.component);
    index.remove(i);
}
