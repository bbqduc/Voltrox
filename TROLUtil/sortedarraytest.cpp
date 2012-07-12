#include <iostream>
#include "sortedarray.h"

int main()
{
	SortedArray<int> arr(256);
	for(int i = 256; i > 0; --i)
		arr.insert(i);

	for(int i = 0; i < 256; ++i)
		assert(arr[i] == i+1);

	std::cout << "ALL TEST PASSED FOR SORTEDARRAY\n";
}
