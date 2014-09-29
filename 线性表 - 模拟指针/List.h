/********************************************************************
	purpose:	模拟指针实现线性表
	author:		xianyun1230
	QQ:         	836663997
	e-mail:    	xianyun1230@163.com
	created:	2014/02/17
*********************************************************************/

#include <iostream>

template<typename T>
class List
{
	public:
		List(int num = 10);
		~List();
		int length(void){return _length;}
		bool empty(void){return _length == 0;}
		bool insert(int k, const T &val);
		bool del(int k, T &val);
		void show(void) const;
	private:
		typedef struct
		{
			T data;
			int link;
		}Node;
		int _length, unusefirst, first;
		Node * node;
};

template<typename T>
List<T>::List(int num)
{
	node = new Node[10];	//分配可用模拟空间
	_length = 0;	//长度为0
	unusefirst = 0;
	first = 0;		//第一个结点的索引
	for (int i = 0; i < num - 1; ++i)	//初始化可用模拟空间
		node[i].link = i + 1;
	node[i].link = -1;	//最后一个
}
template<typename T>
List<T>::~List()
{
	delete [] node;
}
template<typename T>
bool List<T>::insert(int k, const T &val)
{
	if (k < 0 || k > _length || unusefirst == -1)
		return false;
	int numunuse = unusefirst;	//获取可用空间
	unusefirst = node[unusefirst].link;	//可用空间后移
	int loc = first;		//获取插入位置前一结点
	if (k != 0)
		while(--k)
			loc = node[loc].link;
	node[numunuse].data = val;		//插入
	node[numunuse].link = node[loc].link;
	node[loc].link = numunuse;
	++_length;
	return true;
}
template<typename T>
bool List<T>::del(int k, T &val)
{
	if (k < 0 || k >= _length)
		return false;
	if (k != 0)		//不是第一个结点
	{
		int frontloc = first;		//获取删除位置前一结点
		while(--k)
			frontloc = node[frontloc].link;
		int loc = node[frontloc].link;	//获取待删除位置
		val = node[loc].data;
		node[frontloc].link = node[loc].link;
		node[loc].link = unusefirst;	//放入未分配区
		unusefirst = loc;
	}
	else	//是第一个结点
	{
		int temp = node[first].link;
		val = node[first].data;
		node[first].link = unusefirst;	//放入未分配区
		unusefirst = first;
		first = temp;	//新头结点
	}
	--_length;
	return true;
}
template<typename T>
void List<T>::show(void) const
{
	using namespace std;
	cout <<"共" << _length <<"项:\n";
	int ip = first, num = _length;
	while (num--)
	{
		cout <<node[ip].data <<endl;
		ip = node[ip].link;
	}
}