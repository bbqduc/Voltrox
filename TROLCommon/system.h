#pragma once
#include <TROLUtil/memorypool.h>
#include <TROLUtil/sortedarray.h>
#include <stdint.h>
#include "types.h"
#include "message.h"

const ct_t CT_POSITION = 0;
const ct_t CT_PHYSICS = 1;
const ct_t CT_RENDERABLE = 2;

namespace CTFlags
{
    const ct_t POSITION = 1 << CT_POSITION;
    const ct_t PHYSICS = 1 << CT_PHYSICS;
    const ct_t RENDERABLE = 1 << CT_RENDERABLE;
}


template <typename T>
class System
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
    virtual rsp_t handleMessage(Message) = 0;
    System(ct_t id_) :id(id_) {}

    protected:

    MemoryPool<T> mpool;
    SortedArray<Index_t> index;
    const ct_t id;
};

    template <typename T>
T& System<T>::getComponent(eid_t entity)
{
    Index_t t = { entity, 0 };
    int i = index.search(t);
    Index_t ret = index[i];
    assert(ret.entity == entity && ret.component);

    return *ret.component;
}

    template <typename T>
T* System<T>::addComponent(eid_t entity)
{
    // TODO : need some asserts
    T* ret = static_cast<T*>(mpool.alloc());
    Index_t temp = {entity, ret};
    index.insert(temp);
    return ret;
}

    template <typename T>
void System<T>::removeComponent(eid_t entity)
{
    // TODO : some asserts
    Index_t search = {entity, 0};
    int i = index.search(search);
    Index_t temp = index[i];
    mpool.dealloc(temp.component);
    index.remove(i);
}
