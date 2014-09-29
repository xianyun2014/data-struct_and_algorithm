#include<iostream>
#include<ctime>
using namespace std;

template<typename T>
void insertsort(T a[], int n)
{
	T temp;
	int i,j;
	for (i = 1; i < n; ++i)
	{
		temp = a[i];
		for (j = i-1; j >= 0 && a[j] > temp; --j)
			a[j+1] = a[j];
		a[j+1] = temp;
	}
}
int main()
{
	const int n = 10;
	int a[n] = {3,5,1,8,1,2,7,4,9,2};

	insertsort(a,n);

	for (int i = 0; i < n; ++i)
		cout <<a[i] <<endl;
	cin.get();
	cin.get();
	return 0;
}

