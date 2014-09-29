#include <iostream>

using namespace std;

template <typename T>
int LCS(T *a, int m, T *b, int n)
{
	T *c = new T[(m + 1) * (n + 1) + 1]; //模拟二维数组,存放各位置最长公共子序列长度
	T *d = new T[m * n + 1]; //模拟二维数组， 存放方位
	int i, j;
	for (i = 0; i < (m + 1) * (n + 1); ++i)
		c[i] = 0;
	for (i = 1; i <= m; ++i)  //1~m 模拟 0~m-1
	{
		for (j = 1; j <= n; ++j)//1~n 模拟 0~n-1 
		{
			if (a[i - 1] == b[j - 1])
			{
				c[i * (n + 1) + j] = c[(i - 1) * (n + 1) + (j - 1)] + 1; //每行 n+1 个，第i行为 i*(n+1)
				d[(i - 1) * n + j - 1] = 0; //左上方
			}
			else if (c[i * (n + 1) + (j - 1)] > c[(i - 1) * (n + 1) + j])
			{
				c[i * (n + 1) + j] = c[i * (n + 1) + (j - 1)];
				d[(i - 1) * n + j - 1] = 1; //左方
			}
			else
			{
				c[i * (n + 1) + j] = c[(i - 1) * (n + 1) + j];
				d[(i - 1) * n + j - 1] = 2; //上方
			}
		}
	}
	T *result = new T[c[(m + 1)*(n + 1) - 1] + 1];
	for (i = m, j = n; i > 0 && j > 0; )
	{
		int flag = d[(i - 1) * n + j - 1];
		if (flag == 0)
		{
			result[c[i * (n + 1) + j] - 1] = a[i - 1];
			--i;
			--j;
		}
		else if (flag == 1)
		{
			--j;
		}
		else
		{
			--i;
		}
	}
	result[c[(m + 1)*(n + 1) - 1]] = 0;
	cout << result << endl;
	return c[(m+1)*(n+1) - 1];
}
int main()
{
	char a[] = "abcbdabasdfasfdasdfa";
	char b[] = "bdcabaadfasdfxcvzxvasdfasd";
	cout << LCS(a, strlen(a), b, strlen(b));
	cin.get();
	cin.get();
	return 0;
}