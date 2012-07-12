#pragma once

#include <cassert>
#include <cstring>
#include <cstdlib>

template <typename T>
class SortedArray
{
	public:
        static const int NOT_FOUND=-1;
		SortedArray(size_t arrSize_)
            :arr(new T[arrSize_]),
            arrSize(arrSize_),
            items(0)
           {}
		void remove(int index);
		int search(T value) const;
		void insert(T value);
		int size() const { return items; }
		T operator[](int i) const { return arr[i]; }
	private:
		T* arr;
        size_t arrSize;
		int items;

		SortedArray(const SortedArray&);
		SortedArray& operator=(const SortedArray&);
};

#include "sortedarray.inl"
