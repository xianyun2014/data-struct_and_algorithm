#include <iostream>
#include "MaxHBLT.h"

using namespace std;
int main()
{
	MaxHBLT<int> a;
	int b;
	for (int i = 1; i <= 20; ++i)
	{
		b = rand();
		a.insert(b);
	}
	a.show();
	cout <<endl;
	for (int i = 1; i <= 20; ++i)
	{
		a.del(b);
		cout <<"delete:" <<b <<endl;
	}
	a.show();
	for (int i = 1; i <= 20; ++i)
	{
		b = rand();
		a.insert(b);
	}
	a.show();
	cout <<endl;
	cout <<a.high() <<endl;
	cin.get();
	cin.get();
	return 0;
}