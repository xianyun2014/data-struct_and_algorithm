#include<iostream>

using namespace std;

template<typename T>
void selectsort(T a[], int n)	//Ñ¡ÔñÅÅÐò
{
	int loc;	//¼ÇÂ¼Î»ÖÃ
	T temp;	
	bool sorted = true;
	for (int i = n-1; i >= 0; --i)
	{
		loc = i;
		sorted = true;
		for (int t=0; t < i; ++t)
			if (a[t] >= a[loc])
				loc = t;
			else 
				sorted = false;
		if (sorted)
			break;
		temp = a[loc];
		a[loc] = a[i];
		a[i] = temp;
	}
}
int main()
{
	const int n = 5;
	int a[n] = {1,6,2,3,1};
	selectsort(a, n);
	for (int i=0; i< n; ++i)
		cout <<a[i] <<endl;
	return 0;
}