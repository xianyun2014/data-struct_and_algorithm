#include "List.h"

int main()
{
	List<int> link(12);
	link.insert(0,21);
	link.insert(0,12);
	link.insert(2,34);
	link.insert(1,12);
	link.insert(5,13);	//没有第五项，不会插入
	link.show();
	int a;
	link.del(2,a);
	link.show();
	std::cout <<a;
	
	return 0;
}