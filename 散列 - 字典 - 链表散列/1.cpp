#include <iostream>
#include <string>
#include "hashlist.h"

int main()
{
	hashlist<int,std::string> a(12);
	a.insert(12,"abc");
	a.insert(2,"skldjf");
	a.insert(2,"skl");
	a.insert(2,"skldj");
	a.show();
	a.del(12);
	a.del(23);
	a.show();
	return 0;
}