#pragma once

#include <cassert>
#include <cstring>
#include <cstdlib>

template <typename T, int arrSize=1024>
class SortedArray
{
	public:
		SortedArray():items(0){}
		void remove(int index);
		int search(T value);
		void insert(T value);
		int size() { return items; }
		T operator[](int i) { return arr[i]; }
	private:
		T arr[arrSize];
		int items;

		SortedArray(const SortedArray&);
		SortedArray& operator=(const SortedArray&);
};

#include "sortedarray.inl"