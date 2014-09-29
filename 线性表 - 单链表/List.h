/********************************************************************
    purpose:    ��ͷ����ѭ��������
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/13
*********************************************************************/

#include <iostream>


template<typename T>
class List
{
	public:
		List();
		~List();
		bool push_back(const T &val);	//ĩβ��������
		bool push_front(const T &val);	//��ͷ��������
		bool pop_front(T &val);	//��ͷɾ������
		void reverse();	//������
		bool del(const T & val);	//ɾ������ֵΪval ��Ԫ��
		bool erase(int s, int e);	//ɾ��[s,e] ��������
		bool sort();	//��С�������У���������ʵ��
		int count(const T & val);	//ͳ��val ֵ���ֵĴ���
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//����Ԫ�ظ���
		void show() const;	//��������
		T operator[](const int n) const;

	private:
		typedef struct _Node
		{
			T data;
			_Node * next;
		}Node;
		Node * head, * end;	//�ֱ�ָ��ͷ��㡢βָ��
		unsigned int _size;		//Ԫ����
};
template<typename T>
List<T>::List()	//Ĭ�Ϲ��캯��������ͷβ��㣬Ԫ����Ϊ0
{
	_size = 0;
	head = new Node;
	head->next = head;
	end = head;
}
template<typename T>
List<T>::~List()
{
	Node * ph = head, *pt = head->next;
	while(pt != head)
	{
		ph = pt->next;
		delete pt;
		pt = ph;
	}
}
template<typename T>
bool List<T>::push_back(const T & val)
{
	Node *temp = new Node;	//temp������β,next������Ϊhead��ѭ��(ѭ������)
	temp->data = val;
	temp->next = head;
	end->next = temp;
	end = temp;		//ָ����β
	++_size;
	return true;
}
template<typename T>
bool List<T>::push_front(const T &val)
{
	Node *temp = new Node;  
	temp->data = val;
	temp->next = head->next;
	head->next = temp;
	++_size;
	return true;
}
template<typename T>
bool List<T>::pop_front(T &val)
{
	if (_size == 0)
		return 0;
	Node *temp = head->next;
	val = temp->data;		//���ڷ���ֵ
	head->next = temp->next;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return val;
}
template<typename T>
void List<T>::reverse()	//����ǰ�˾͵ص���
{
	if (_size < 2)
		return;
	Node * ps = head->next;	//��β
	Node * pn = ps->next;	//�ӵڶ�����㿪ʼδ�����ò���
	Node * pnn = pn->next;	//pnn��Ǵ����ò���
	while(pn != head)		//����β��ѭ����head
	{
		pn->next = head->next;	//pn�����ѵ��ò���
		head->next = pn;	//head�����ѵ��ò���
		pn = pnn;	
		pnn = pnn->next;	//δ���ò��ֺ���
	}
	ps->next = head;	//psָ���Ϊ�ѵ��ò������һ����㣬ָ��head��֤ѭ��
	end = ps;
}
template<typename T>
bool List<T>::del(const T &val)
{
	bool deled = false;
	if (_size > 0)
	{
		Node * pt = new Node;
		Node * pl = pt;
		Node * temp = pl;		//�����ͷ��ڴ�
		pl->next = head->next;
		while(pl != head)
		{
			if (pl->next->data == val)
			{
				temp = pl->next;	//�洢��ɾλ��
				pl->next = pl->next->next;	//�����ɾ���
				delete temp;	//�ͷ��ڴ�
				--_size;
				deled = true;
			}
			pl = pl->next;
		}
		if (_size == 0)
			end = head;
		delete pt;
	}
	return deled;
}
template<typename T>
bool List<T>::erase(int s, int e) //ɾ��[s,e]����
{
	if (e<s || s<0 || e >= _size)
		return false;
	int num = s;
	Node * ps = head;
	while(num--)
		ps = ps->next;	//�ҵ��±�Ϊs ��Ԫ�ص�ǰһ��Ԫ��
	num = e - s + 1;			//�ͷ�e - s + 1 ��Ԫ��
	Node * pe = ps->next;
	Node * pt = pe;
	while(num--)
	{
		pe = pe->next;
		delete pt;
		pt = pe;
	}
	ps->next = pe;		//ƴ��
	return true;
}


template<typename T>
bool List<T>::sort()	//���������㷨
{
	if (_size >= 2)
	{
		Node * ps = head->next->next;	//ָ��δ��������
		Node *pi, *pt;
		head->next->next = NULL;	//����������(��һ�����)ĩβ����NULL���������
		while(ps != head)
		{
			for (pi = head; (pi->next != NULL) && (pi->next->data <= ps->data); pi = pi->next)	//���Ҳ���λ��
				continue;
			pt = ps;		//��ȡ�����ڵ�
			ps = ps->next;		//δ����������
			if (pi->next != NULL)	//�ж��Ƿ�Ϊ�����������ֵ
			{
				pt->next = pi->next;
				pi->next = pt;
			}
			else
			{
				pi->next = pt;
				pt->next = NULL;	//Ϊ���ֵ������β��NULL���
			}
		}
		pt = head->next;	//Ѱ��NULLǰ��һ���ڵ�
		while(pt->next)
			pt = pt->next;
		pt->next = head;	//ѭ��
	}
	return true;
}
template<typename T>
int List<T>::count(const T &val)
{
	int n = 0;
	Node * ps = head->next;
	while(ps != head)
	{
		if (ps->data == val)
			++n;
		ps = ps->next;
	}
	return n;
}

template<typename T>
void List<T>::show()const
{
	Node * temp = head->next;
	std::cout <<"�������ݹ�" <<size() <<"������������:\n";
	while(temp != head){
		std::cout <<temp->data <<std::endl;
		temp = temp->next;
	}
}
template<typename T>
T List<T>::operator[](const int n) const
{
	if (n < 0 || n >= _size)
		return 0;
	int num = n;
	Node * pt = head->next;
	while(num--)
		pt = pt->next;
	return pt->data;
}
