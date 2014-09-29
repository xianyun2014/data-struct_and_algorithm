/********************************************************************
	purpose:	ģ��ָ��ʵ�����Ա�
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
	node = new Node[10];	//�������ģ��ռ�
	_length = 0;	//����Ϊ0
	unusefirst = 0;
	first = 0;		//��һ����������
	for (int i = 0; i < num - 1; ++i)	//��ʼ������ģ��ռ�
		node[i].link = i + 1;
	node[i].link = -1;	//���һ��
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
	int numunuse = unusefirst;	//��ȡ���ÿռ�
	unusefirst = node[unusefirst].link;	//���ÿռ����
	int loc = first;		//��ȡ����λ��ǰһ���
	if (k != 0)
		while(--k)
			loc = node[loc].link;
	node[numunuse].data = val;		//����
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
	if (k != 0)		//���ǵ�һ�����
	{
		int frontloc = first;		//��ȡɾ��λ��ǰһ���
		while(--k)
			frontloc = node[frontloc].link;
		int loc = node[frontloc].link;	//��ȡ��ɾ��λ��
		val = node[loc].data;
		node[frontloc].link = node[loc].link;
		node[loc].link = unusefirst;	//����δ������
		unusefirst = loc;
	}
	else	//�ǵ�һ�����
	{
		int temp = node[first].link;
		val = node[first].data;
		node[first].link = unusefirst;	//����δ������
		unusefirst = first;
		first = temp;	//��ͷ���
	}
	--_length;
	return true;
}
template<typename T>
void List<T>::show(void) const
{
	using namespace std;
	cout <<"��" << _length <<"��:\n";
	int ip = first, num = _length;
	while (num--)
	{
		cout <<node[ip].data <<endl;
		ip = node[ip].link;
	}
}