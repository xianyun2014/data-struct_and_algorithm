#include <iostream>
#include "MaxHeap.h"

template <typename T>
void HeapSort(T a[], int num)
{
	MaxHeap<T> heap(a, num, num);

	T tmp;
	for (int i = num ; i >= 1; --i)
	{
		heap.del(tmp);
		a[i] = tmp;
	}
	heap.freeown(); //释放所有权
}

int main()
{
	int a[30 + 1];
	for (int i = 1; i <= 30; ++i)
		a[i] = rand();
	HeapSort(a, 30);
	for (int i = 1; i <= 30; ++i)
		std::cout <<a[i] <<" ";
	std::cout <<std::endl;
	std::cin.get();
	std::cin.get();
	return 0;
}