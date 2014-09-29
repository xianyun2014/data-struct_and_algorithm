#include<iostream>
using namespace std;

template<class T>
void perm(T arr[], int m, int n) //arr[m:n]ееап
{
	int i;
	if (m == n)
	{
		for (i=0; i <= n; i++)
			cout <<arr[i] ;
		cout <<endl;
	}
	else
		for (i = m; i <= n; i++)
		{
			swap(arr[i], arr[m]);
			perm(arr, m+1, n);
			swap(arr[i], arr[m]);
		}
}

int main(int argc, char *argv[])
{
	int a[] = {1,2,3,4};
	perm(a,0,3);
	return 0;
}