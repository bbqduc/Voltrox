#pragma once

#include <cassert>
#include <stdint.h>
#include <LinearMath/btScalar.h>

template <typename T, int size=1024>
class ATTRIBUTE_ALIGNED16(MemoryPool)
{
	public:
		// Condition is necessary because the pointer to the next free position stored in a free position
		MemoryPool() { assert(sizeof(T) >= sizeof(void*)); initFreePointers(); } 
		
		// Return address for a new slot
		// Currently just fails an assert if out of space
		inline void* alloc();

		// !!!!  Bad things happen if you free a slot that is not allocated or not inside this pool !!!!
		inline void dealloc(void*);

		bool hasSpace() { return nextFreeSlot != 0; }

	private:
		uint8_t pool[size*sizeof(T)];
		void* nextFreeSlot;

		inline void initFreePointers();

		MemoryPool(const MemoryPool&);
		MemoryPool& operator=(const MemoryPool&);
};

#include "memorypool.inl"
