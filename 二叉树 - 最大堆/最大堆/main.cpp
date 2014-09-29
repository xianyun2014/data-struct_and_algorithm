#include <iostream>
#include "maxheap.h"

int main()
{
	MaxHeap<int> a(30);
	int c[32];
	for (int i = 1 ; i <= 30; i++)
	{
		c[i] = rand();
		a.insert(c[i]);
	}
	a.showonlevel();
	std::cout <<std::endl;
	MaxHeap<int> b(c, 30,40);
	b.showonlevel();
	std::cout <<std::endl;
	std::cin.get();
	return 0;
}