#include <cassert>
#include <cstring>
#include <cstdlib>

template<typename T, int size_=256>
class SortedArray
{
	public:
		SortedArray():items(0){}
		void remove(int index);
		int search(T value);
		int insert(T value);
		int size() { return items; }
		T operator[](int i) { return array[i]; }
	private:
		T array[size_];
		int items;
};

#include "sortedarray.inl"
