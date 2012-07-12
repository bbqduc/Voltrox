#include "componentstore.h"

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
