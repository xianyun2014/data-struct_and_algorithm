#include <iostream>
#include "List.h"
using namespace std;

int main()
{
	List<int> link;
	link.push_back(31);
	link.push_front(23);
	link.push_back(12);
	link.push_back(32);
	link.push_back(76);
	link.push_back(93);
	link.push_back(34);
	link.show();
	link.reverse();
	link.del(12);
	link.show();
	link.sort();
	link.show();
	link.reverse();
	link.show();
	cout <<link.count(76) <<endl;
	cout <<"end!\n";
	cin.get();
	cin.get();
	return 0;
}
