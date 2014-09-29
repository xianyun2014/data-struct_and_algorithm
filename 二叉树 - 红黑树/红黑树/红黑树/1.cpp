#include <iostream>
#include "RBTree.h"
using namespace std;
int main()
{     
	RBTree<int> a;
	for (int i = 0; i < 10; ++i)
	{	
		a.insert(i);
		a.show();
		cout << endl;
	}
		
	for (int i = 0; i < 10; ++i)
	{
		a.del(i);
		a.show();
		cout << endl;
	}

	cout << endl;
	cout << "ok\n";
	cin.get();
	cin.get();
	return 0;
}