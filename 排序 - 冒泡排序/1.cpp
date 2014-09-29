#include<iostream>
#include<ctime>
using namespace std;

template<typename T>
void bublesort(T a[], int n)
{
	T temp;
	bool sorted;	//Ã»Ã°ÅÝÊ±ÍË³ö
	for (int k = n-1; k >= 0; --k)
	{
		sorted = true;
		for (int i = 0; i < k; ++i)
			if (a[i] > a[i+1])
			{
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
				sorted = false;
			}
		if (sorted)
			break;
	}
}
int main()
{
	const int n = 6;
	int a[n] = {3,5,1,8,1,2};

	bublesort(a,n);

	for (int i = 0; i < n; ++i)
		cout <<a[i] <<endl;
	cin.get();
	cin.get();
	return 0;
}

