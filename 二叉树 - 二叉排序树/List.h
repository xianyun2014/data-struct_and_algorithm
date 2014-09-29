/********************************************************************
    purpose:    ��ͷ����˫����
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/18
*********************************************************************/
template<typename T>
class List
{
	public:
		List();
		~List();
		bool push_back(const T &val);	//ĩβ��������
		bool push_front(const T &val);	//��ͷ��������
		bool pop_front(T &val);	//��ͷɾ������
		bool pop_back(T &val);
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//����Ԫ�ظ���

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
		return false;
	Node *temp = head->next;
	val = temp->data;		//���ڷ���ֵ
	head->next = temp->next;
	temp->next->front = head;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return true;
}
template<typename T>
bool List<T>::pop_back(T &val)
{
	if (_size == 0)
		return false;
	Node *temp = end;
	val = end->data;		//���ڷ���ֵ
	end = end->front;
	end->next = head;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return true;
}
