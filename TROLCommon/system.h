#pragma once
#include "../TROLUtil/memorypool.h"
#include "../TROLUtil/sortedarray.h"
#include <stdint.h>

typedef uint64_t ct_t; // Component type
typedef uint32_t eid_t; // Entity id type
typedef uint8_t rsp_t; // Response type 
typedef uint8_t msg_t; // Message type

const ct_t CT_POSITION = 0;
const ct_t CT_PHYSICS = 1;
const ct_t CT_RENDERABLE = 2;

const ct_t CTF_POSITION = 1 << CT_POSITION;
const ct_t CTF_PHYSICS = 1 << CT_PHYSICS;
const ct_t CTF_RENDERABLE = 1 << CT_RENDERABLE;

struct Message
{
	msg_t mType;
	eid_t entity;
	void* data;
};

template <typename T>
class System
{
	struct Index_t
	{
		eid_t entity;
		T* component;
		bool operator<(const Index_t& a) { return entity < a.entity; }
	};

	SortedArray<Index_t>& getComponents() { return index; }
	T* addComponent(eid_t entity);
	void removeComponent(eid_t entity);
	virtual rsp_t handleMessage(Message) = 0;

	protected:

	MemoryPool<T> mpool;
	SortedArray<Index_t> index;
	const ct_t id;
};

template <typename T>
T& System::getComponent(eid_t entity)
{
	Index_t t = { entity, 0 };
	int i = index.search(t);
	Index_t& ret = index.get(i);
	assert(ret.entity == entity && ret.component);

	return ret;
}

template <typename T>
T* System::addComponent(eid_t entity)
{
	// TODO : need some asserts
	T* ret = mpool.alloc();
	Index_t temp = {entity, ret};
	index.insert(temp);
	return ret;
}

template <typename T>
void System::removeComponent(eid_t entity)
{
	// TODO : some asserts
	Index_t search = {entity, 0}
	int i = index.search(search);
	Index_t& temp = index[i];
	mpool.dealloc(temp.component);
	index.remove(i);
}