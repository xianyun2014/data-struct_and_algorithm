#include <iostream>
#include <string>
#include "skiplist.h"
int main()
{
	skiplist<int,std::string> lst(INT_MAX, 100);
	lst.insert(12, "one");
	lst.insert(1000,"two"); 
	lst.insert(234, "three");
	lst.show();
	lst.del(12);
	lst.show();
	lst.del(234);
	lst.show();
	std::cout.put('a');
	std::cin.get();
	return 0;
}