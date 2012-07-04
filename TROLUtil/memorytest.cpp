#include "memorypool.h"
#include <cassert>
#include <iostream>

struct Test
{
	int a;
	int b;
	char c;
};

int main()
{
	Test* t[256];
	MemoryPool<Test> mpool;
	for(int i = 0; i < 256; ++i)
	{
		t[i] = new (mpool.alloc()) Test;
		t[i]->a = i;
		t[i]->b = 256-i;
		t[i]->c = 'a';
	}
	assert(!mpool.hasSpace());
	mpool.dealloc(t[0]);
	assert(mpool.hasSpace());
	mpool.dealloc(t[1]);

	t[1] = new (mpool.alloc()) Test;
	t[1]->a = 1024;
	t[1]->b = 2048;
	t[1]->c = 'z';


	for(int i = 2; i < 256; ++i)
	{
		assert(t[i]->a == i);
		assert(t[i]->b == 256-i);
		assert(t[i]->c == 'a');
	}

	assert(t[1]->a == 1024);
	assert(t[1]->b == 2048);
	assert(t[1]->c == 'z');

	std::cout << "All test passed for memorypool.\n";

	return 0;

}
