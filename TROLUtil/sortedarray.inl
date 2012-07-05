template<typename T, int size_>
int SortedArray<T, size_>::insert(T value)
{
	assert(items+1 <= size_);
	int base = 0, top = items;
	while(base != top)
	{
		int t = (base + top) / 2;
		if(value < array[t]) top = t;
		else base = t+1;
	}
	assert(array[base] != value);
	memmove(&array[base+1], &array[base], sizeof(T)*(items-base));
	array[base] = value;
	++items;
}

template<typename T, int size>
int SortedArray<T, size>::search(T value)
{
	assert(items);
	int base = 0, top = items-1;
	while(base != top)
	{
		int t = (base + top) / 2;
		if(value <= array[t]) top = t;
		else base = t+1;
	}
	assert(array[base] == value);
	return base;
}

template<typename T, int size>
void SortedArray<T, size>::remove(int i)
{
	assert(i >= 0 && i < items);
	memmove(&array[i], &array[i+1], sizeof(T)*(--items -i));
}
