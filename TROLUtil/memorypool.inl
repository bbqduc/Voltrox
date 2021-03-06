	template<typename T, int size>
void* MemoryPool<T,size>::alloc()
{
	assert(nextFreeSlot);
	void* t = nextFreeSlot;
	nextFreeSlot = *(void**)(nextFreeSlot);
	assert(t >= &pool[0] && t <= &pool[(size-1)*sizeof(T)]);
	return t;
}

	template<typename T, int size>
void MemoryPool<T,size>::dealloc(void* h)
{
	assert(h >= &pool[0] && h <= &pool[(size-1)*sizeof(T)]);
	((T*)h)->~T();
	*(void**)(h) = nextFreeSlot;
	nextFreeSlot = h;
}

	template<typename T, int size>
void MemoryPool<T,size>::initFreePointers()
{
	for(int i = 0; i < size-1; ++i) 
		*(void**)(&pool[sizeof(T)*i]) = &pool[sizeof(T)*(i+1)];
	*(void**)(&pool[sizeof(T)*(size-1)]) = 0;
	nextFreeSlot = &pool[0];
}
