#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int NUM = 100;  //�������ݴ�С
const int SortFunNum = 8;

template <typename T> void BubleSort(T a[], int, int);
template <typename T> void SelectSort(T a[], int, int);
template <typename T> void InsertSort(T a[], int, int);
template <typename T> void RankSort(T a[], int, int);
template <typename T> void Merge(T a[], int, int , int);
template <typename T> void MergeSort(T a[], int, int);
template <typename T> int  Partition(T a[], int, int);
template <typename T> void QuickSort(T a[], int, int);
template <typename T> void ShellSort(T a[], int, int);
template <typename T> void HeapSort(T a[], int, int);

void Test()
{
	cout << "���ݳ�ʼ����..." << endl;
	int **testData = new int *[SortFunNum];
	for (int i = 0; i < SortFunNum; ++i)
		testData[i] = new int[NUM];
	for (int k = 0; k < NUM; ++k)
	{
		testData[0][k] = rand();
		for (int j = 1; j < SortFunNum; ++j)
			testData[j][k] = testData[0][k];
	}
	cout << "���ݳ�ʼ�����!" << endl;
	clock_t begin, end;

	begin = clock();
	HeapSort(testData[6], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "��������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;

	begin = clock();
	QuickSort(testData[5], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "����������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;

	begin = clock();
	MergeSort(testData[4], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "�鲢������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;

	
	begin = clock();
	InsertSort(testData[2], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "����������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;
/**/
	begin = clock();
	ShellSort(testData[7], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "ϣ��������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;

	begin = clock();
	SelectSort(testData[1], 0, NUM - 1);
	end = clock();
	cout <<setw(20) << "ѡ��������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;
	
	begin = clock();
	RankSort(testData[3], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "����������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;

	begin = clock();
	BubleSort(testData[0], 0, NUM - 1);
	end = clock();
	cout << setw(20) << "ð��������ʱ: " << setw(4) << (end - begin) / CLOCKS_PER_SEC << "��" << setw(4) <<
		1000 * double((end - begin) % CLOCKS_PER_SEC) / CLOCKS_PER_SEC << "����" << endl;
	
	
	for (int i = 0; i < SortFunNum; ++i)
		delete[] testData[i];
	delete[] testData;
}

int main()
{
	srand(time(0));
	while (1)
	{
		cout << "����������ݳ���: ";
		cin >> NUM;
		Test();
		cout << "�������!" << endl << endl;;
	}
	
	cin.get();
	cin.get();
	return 0;
}












/*ð������*/
template <typename T>
void BubleSort(T a[], int first, int last)
{
	int has = 1;
	for (int i = last; i > first && has; --i)
	{
		has = 0;
		for (int j = first; j < i; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				has = 1;
			}

		}
	}
}

/*ѡ������*/
template <typename T>
void SelectSort(T a[], int first, int last)
{
	int m;
	for (int i = last; i > first; --i)
	{
		m = i;
		for (int j = first; j < i; ++j)
		{
			if (a[j] > a[m])
				m = j;
		}
		swap(a[m], a[i]);
	}
}


/*��������*/
template <typename T>
void InsertSort(T a[], int first, int last)
{
	int j;
	T t;
	for (int i = first + 1; i <= last; ++i)
	{
		t = a[i];
		j = i - 1;
		while (a[j] > t && j >= 0)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = t;
	}
}

/*��������*/
template <typename T>
void RankSort(T a[], int first, int last)
{
	int sum = last - first + 1;
	int *rank = new int[sum];
	T *b = new T[sum];
	for (int i = 0; i < sum; ++i)
	{
		rank[i] = 0;
		b[i] = a[first + i];
	}

	for (int m = first; m <= last; ++m)
	{
		for (int n = first; n < m; ++n)
		{
			if (a[m] > a[n])
				rank[m - first]++;
			else
				rank[n - first]++;
		}
	}
	for (int k = 0; k < sum; ++k)
	{
		a[first + rank[k]] = b[k];
	}
	delete[] b;
	delete[] rank;
}

/*�鲢�����ڹ鲢����*/
template <typename T>
void Merge(T a[], int first, int mid, int last)
{
	if (last - first < 1)
		return;
	T *b = new T[last - first + 1];
	int m = first, n = mid, bi = -1;
	while (m < mid && n <= last)
	{
		if (a[m] > a[n])
			b[++bi] = a[n++];
		else
			b[++bi] = a[m++];
	}
	while (m < mid)
		b[++bi] = a[m++];
	while (n <= last)
		b[++bi] = a[n++];
	while (bi >= 0)
	{
		a[first + bi] = b[bi];
		--bi;
	}

	delete[] b;

}
/*�鲢����*/
template <typename T>
void MergeSort(T a[], int first, int last)
{
	if (last - first + 1 >= 2)
	{
		int mid = (first + last) / 2;
		MergeSort(a, first, mid);
		MergeSort(a, mid + 1, last);
		Merge(a, first, mid + 1, last);
	}
}

/*���֣����ڿ�������*/
template <typename T>
int Partition(T a[], int first, int last)
{
	swap(a[rand() % (last - first + 1) + first], a[last]); //�������
	int m = last;
	int j = first - 1;
	for (int i = first; i < last; ++i)
	{
		if (a[i] < a[m])
		{
			++j;
			swap(a[j], a[i]);
		}
	}
	swap(a[m], a[j + 1]);
	return j + 1;

}
/*��������*/
template <typename T>
void QuickSort(T a[], int first, int last)
{
	if (last - first + 1 >= 2)
	{
		int m = Partition(a, first, last);
		QuickSort(a, first, m - 1);
		QuickSort(a, m + 1, last);
	}
}

/*ϣ������*/
template <typename T>
void ShellSort(T a[], int first, int last)
{
	int sum = last - first + 1;
	T t;
	int j;

	for (int d = sum / 2; d >= 1; d /= 2)
	{
		for (int i = d; i < sum; i++)
		{
			t = a[first + i];
			j = i - d;
			while (j >= 0 && a[first + j] > t)
			{
				a[first + j + d] = a[first + j];
				j -= d;
			}
			a[first + j + d] = t;
		}
	}
}

/*������*/
template <typename T>
void HeapSort(T a[], int first, int last)
{
	int num = last - first + 1;
	int f, c;
	T t;
	for (f = num / 2; f >= 1; --f)
	{
		c = f * 2;
		t = a[first - 1 + f];
		while (c < num)
		{
			if (c + 1 <= num && a[first + c] > a[first - 1 + c])
				++c;
			if (t > a[first - 1 + c])
				break;
			a[first - 1 + c / 2] = a[first - 1 + c];
			c *= 2;
		}
		a[first - 1 + c / 2] = t;
	}

	while (num > 1)
	{
		swap(a[first], a[first + num - 1]);
		c = 2;
		t = a[first];

		while (c < num)
		{
			if (c + 1 < num && a[first + c] > a[first - 1 + c])
				++c;
			if (a[first - 1 + c] < t)
				break;
			a[first - 1 + c / 2] = a[first - 1 + c];
			c *= 2;
		}
		a[first - 1 + c / 2] = t;
		--num;
	}
}

