/********************************************************************
	purpose:	公式化描述实现线性表
	author:		xianyun1230
	QQ:		836663997
	e-mail:		xianyun1230@163.com
	created:	2014/02/16	
*********************************************************************/
#include <iostream>

template<typename T>
class List
{
	public:
		List(int MaxListSize = 10);
		~List();
		bool empty() const { return _length == 0;}
		int length() const { return _length;}
		int search(const T &x) const;
		bool del(int k,T &val);
		bool insert(int k, const T& x);
		void show();
		T operator [](int i){return element[i];}
	private:
		int _length;
		T *element;
		int MaxSize;
};
template<typename T>
List<T>::List(int MaxListSize)
{
	MaxSize = MaxListSize;
	_length = 0;
	element = new T[MaxSize];
}
template<typename T>
List<T>::~List()
{
	delete [] element;
}
template<typename T>
int List<T>::search(const T &x) const
{
	for (int i = 0; i < _length && element[i] != x; ++i)
		continue;
	if (i != _length)
		return i-1;
	else
		return -1;
}
template<typename T>
bool List<T>::del(int k, T &val)
{
	if (k < 0 || k >= _length)
		return false;
	int n = k;
	val = element[n];
	while(n < _length - 1)
	{
		element[n] = element[n+1];
		++n;
	}
	--_length;
	return true;	
}
template<typename T>
bool List<T>::insert(int k, const T& x)
{
	if (k < 0 || k > _length || _length == MaxSize)
		return false;
	int n = _length - 1;
	while (k <= n)
	{
		element[n + 1] = element[n];
		--n;
	}
	element[k] = x;
	++_length;
	return true;
}
template<typename T>
void List<T>::show()
{
	using namespace std;
	cout <<"共" <<_length <<"项:" <<endl;
	for (int i=0; i < _length; ++i)
		cout <<element[i] <<endl;
}