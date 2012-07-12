void* MemoryPool::alloc()
{
	assert(nextFreeSlot);
	void* t = nextFreeSlot;
	nextFreeSlot = *(void**)(nextFreeSlot);
	assert(t >= &pool[0] && t <= &pool[(maxEntries-1)*entrySize]);
	return t;
}

void MemoryPool::dealloc(void* h)
{
	assert(h >= &pool[0] && h <= &pool[(maxEntries-1)*entrySize]);
	*(void**)(h) = nextFreeSlot;
	nextFreeSlot = h;
}

void MemoryPool::initFreePointers()
{
	for(int i = 0; i < maxEntries-1; ++i) 
		*(void**)(&pool[entrySize*i]) = &pool[entrySize*(i+1)];
	*(void**)(&pool[entrySize*(maxEntries-1)]) = 0;
	nextFreeSlot = &pool[0];
}
