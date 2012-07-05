#include <iostream>
#include "sortedarray.h"

int main()
{
	SortedArray<int,256> arr;
	for(int i = 256; i > 0; --i)
		arr.insert(i);

	for(int i = 0; i < 256; ++i)
		assert(arr[i] == i+1);
}
