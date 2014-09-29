#include <iostream>

template <typename T>
class MaxHeap
{
public:
	MaxHeap(int num);
	MaxHeap(T Arr[], int arrsize, int totalsize);
	bool insert(const T&);
	bool del(T&);
	void show() const;
	void showonlevel() const;
private:
	T* arr;
	int size, max_size;
};

template <typename T>
MaxHeap<T>::MaxHeap(int num)
{
	arr = new T [num + 1];
	max_size = num;
	size = 0;
}

template <typename T>
MaxHeap<T>::MaxHeap(T Arr[], int arrsize, int totalsize)
{
	arr = new T [totalsize + 1];
	max_size = totalsize;
	size = arrsize;
	arr = Arr;
	
	int loc, cloc;
	
	for (loc = size/2; loc >= 1; --loc)
	{
		T tmp = arr[loc];
		cloc = loc * 2;
		while (cloc <= size)
		{
			if (cloc < size && arr[cloc + 1] > arr[cloc])
				++cloc;
			if (tmp > arr[cloc])
				break;
			arr[cloc/2] = arr[cloc];
			cloc *= 2;
		}
		arr[cloc/2] = tmp;
	}
}
		


template <typename T>
bool MaxHeap<T>::insert(const T& val)
{
	if (size == max_size)
		return false;
	int num = ++size;
	while (num > 1 && val > arr[num/2])
	{
		arr[num] = arr[num/2];
		num /= 2;
	}
	arr[num] = val;
	return true;
}

template <typename T>
bool MaxHeap<T>::del(T& val)
{
	if (size == 0)
		return false;
	val = arr[1];
	T tmp = arr[size--];
	int loc = 1, cloc = 2;
	while (cloc <  size)
	{
		if (cloc < size && arr[cloc + 1] > arr[cloc])
			++cloc;
		if (tmp > arr[cloc])
			break;
		arr[loc] = arr[cloc];
		loc = cloc;
		cloc *= 2;
	}
	arr[loc] = tmp;
	return true;
}

template <typename T>
void MaxHeap<T>::show()const
{
	for (int i = 1; i <= size; ++i)
		std::cout <<arr[i] <<" ";
	std::cout <<std::endl;
}

template <typename T>
void MaxHeap<T>::showonlevel()const
{
	int k = 1;
	for (int i = 1; i <= size; ++i)
	{
		std::cout <<arr[i] <<" ";
		if (i == k)
		{
			std::cout <<std::endl;
			k = k*2 + 1;
		}
	}
	std::cout <<std::endl;
}