/********************************************************************
    purpose:    带头结点的双链表
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
		bool push_back(const T &val);	//末尾插入数据
		bool push_front(const T &val);	//开头插入数据
		bool pop_front(T &val);	//开头删除数据
		bool pop_back(T &val);
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//返回元素个数

	private:
		typedef struct _Node
		{
			T data;
			_Node *next, *front;
		}Node;
		Node * head, * end;	//分别指向头结点、尾指针
		unsigned int _size;		//元素数
};
template<typename T>
List<T>::List()	//默认构造函数，创建头尾结点，元素数为0
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
	Node *temp = new Node;	//temp用作新尾,next属性设为head以循环(循环链表)
	temp->front = end;
	temp->data = val;
	temp->next = head;
	end->next = temp;
	end = temp;		//指向新尾
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
	val = temp->data;		//用于返回值
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
	val = end->data;		//用于返回值
	end = end->front;
	end->next = head;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return true;
}
