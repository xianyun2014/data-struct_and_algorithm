/*计数排序*/

#include<iostream>
#include<cstring>
using namespace std;

template<class T>
void Rand(T a[], int n, int r[])	//计算名次
{
	int i,j;
	for (i = 0; i < n; i++)
		r[i] = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < i; j++)
			if (a[j] <= a[i]) r[i]++;
			else r[j]++;
}
template<class T>
void Rearrange(T a[], int n, int r[])
{   //按序重排数组a中的元素，使用附加数组u
	T *u = new T[n];
	int i;
	for (i = 0; i < n; i++)
		u[r[i]] = a[i];

	for (i = 0; i < n; i++)
		a[i] = u[i];
	delete []u;
}
int main(int argc, char *argv[])
{
	const int n = 6;
	int i;
	int a[n] = {1,2,2,5,2,5};
	int r[n];
	Rand(a, n, r);
	for (i= 0; i < n; i++)
		cout << a[i] <<"  " << r[i] <<endl;
	cout <<endl;
	Rearrange(a, n, r);
	for (i= 0; i < n; i++)
		cout << a[i] <<endl;
	return 0; 
}