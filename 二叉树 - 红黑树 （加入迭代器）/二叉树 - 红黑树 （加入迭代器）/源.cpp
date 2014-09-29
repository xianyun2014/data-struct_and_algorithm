#include <iostream>
#include "RBTree.h"

using namespace std;

int main()
{
	RBTree<int> a;
	for (int i = 0; i < 10; ++i)
		a.Insert(i);
	a.show();
	for (int i = 2; i < 5; ++i)
		a.Del(i);
	a.show();
	cin.get();
	return 0;

}