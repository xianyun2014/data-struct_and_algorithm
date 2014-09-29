/********************************************************************
	purpose:	间接寻址实现线性表
	author:		xianyun1230
	QQ:		836663997
	e-mail:		xianyun1230@163.com
	created:	2014/02/17
*********************************************************************/

#include <iostream>

template<typename T>
class List
{
	public:
		List(int MaxListSize = 10);
		~List();
		bool empty() const {return _length == 0;}
		int length() const {return _length;}
		int search(const T& x) const;
		bool del(int k, T &val);
		bool insert(int k, const T& x);
		void show() const;
	private :
		T **table;		//table指向数组，数组中存储类型T 的指针
		int _length,MaxSize;
};
template<typename T>
List<T>::List(int MaxListSize)
{
	MaxSize = MaxListSize;
	table = new T *[MaxSize];
	_length = 0;
}
template<typename T>
List<T>::~List()
{
	for (int i = 0; i < _length; i++)
	delete table[i];
	delete [] table;
}
template<typename T>
bool List<T>::del(int k, T &val)
{	
	if (k < 0 || k >= _length)
		return false;
	val = *table[k];
	delete table[k];
	for (int i = k; i < _length - 1; i++)
		table[i] = table[i+1];
	_length--;
	return true;
}

template<typename T>
bool List<T>::insert(int k, const T& x)
{	
	if (k < 0 || k > _length || _length == MaxSize)
		return false;
	for (int i = _length - 1; i >= k; i--)
		table[i+1] = table[i];
	table[k] = new T;
	*table[k] = x;
	_length++;
	return true;
}
template<typename T>
void List<T>::show() const
{
	std::cout <<"共" <<_length <<"项:\n";
	for (int i=0; i < _length; ++i)
		std::cout <<*table[i] <<std::endl;
}