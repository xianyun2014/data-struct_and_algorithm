/********************************************************************
    purpose:    ��ͷ����˫����
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/18
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
		int count(const T & val);	//ͳ��val ֵ���ֵĴ���
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//����Ԫ�ظ���
		void show() const;	//��������
		T operator[](const int n) const;

	private:
		typedef struct _Node
		{
			T data;
			_Node *next, *front;
		}Node;
		Node * head, * end;	//�ֱ�ָ��ͷ��㡢βָ��
		unsigned int _size;		//Ԫ����
};
template<typename T>
List<T>::List()	//Ĭ�Ϲ��캯��������ͷβ��㣬Ԫ����Ϊ0
{
	_size = 0;
	head = new Node;
	head->front = head;
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
	temp->front = end;
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
	temp->front = head;
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
	temp->next->front = head;
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
		pn->front = head;
		head->next->front = pn;	//head�����ѵ��ò���
		head->next = pn;
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
				temp->next->front = pl;
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
	Node *temp = head->next;
	std::cout <<"�������ݹ�" <<size() <<"������������:\n";
	while(temp != head){
		std::cout <<temp->data <<std::endl;
		temp = temp->next;
	}
	std::cout <<"�����������" <<size() <<"������������:\n";
	temp = end;
	while(temp != head){
		std::cout <<temp->data <<std::endl;
		temp = temp->front;
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
