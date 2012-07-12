#include <iostream>

template<typename T>
void SortedArray<T>::insert(T value)
{
	assert(items+1 <= arrSize);
	int base = 0, top = items;
	while(base != top)
	{
		int t = (base + top) / 2;
		if(value < arr[t]) top = t;
		else base = t+1;
	}
	assert(base == items || arr[base] != value);
	memmove(&arr[base+1], &arr[base], sizeof(T)*(items-base));
	arr[base] = value;
	++items;
}

template<typename T>
int SortedArray<T>::search(T value) const
{
	assert(items);
	int base = 0, top = items-1;
	while(base != top)
	{
		int t = (base + top) / 2;
		if(value <= arr[t]) top = t;
		else base = t+1;
	}
	if(arr[base] != value)
        base = NOT_FOUND;
	return base;
}

template<typename T>
void SortedArray<T>::remove(int i)
{
	assert(i >= 0 && i < items);
	memmove(&arr[i], &arr[i+1], sizeof(T)*(--items -i));
}
