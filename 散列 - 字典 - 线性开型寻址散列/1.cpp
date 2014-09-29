#include <iostream>
#include <ctime>
#include "hashtable.h"

int main()
{
	hashtable<int,int> a(12);
	for (int i = 0; i < 10; i++)
		a.insert(rand(),rand());
	a.insert(23,34);
	a.show();
	a.del(23);
	a.show();
	return 0;
}