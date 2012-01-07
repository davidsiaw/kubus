#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array
{
	T* buffer;
	size_t buffer_size;
	size_t element_count;

public:
	typedef int(*comparer)(const T* a, const T* b);

	Array()
	{
		buffer = (T*)malloc(sizeof(T));
		buffer_size = 1;
		element_count = 0;
	}
	
	~Array()
	{
		free(buffer);
	}

	void Insert(T item)
	{
		if (element_count == buffer_size)
		{
			buffer_size *= 2;
			buffer = (T*)realloc(buffer, buffer_size * sizeof(T));
		}

		buffer[element_count] = item;

		element_count++;
	}

	static int defaultComparer(const T* a, const T* b)
	{
		return (int)(a-b);
	}

	void Sort()
	{
		Sort(defaultComparer);
	}

	void Sort(comparer c)
	{
		qsort(buffer, element_count, sizeof(T), (int(*)(const void*, const void*)) c);
	}

	size_t Count() const
	{
		return element_count;
	}

	const T* GetBuffer()
	{
		return buffer;
	}

};

#endif // ARRAY_H