/********************************************************************
    purpose:    带头结点的循环单链表
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
		bool push_back(const T &val);	//末尾插入数据
		bool push_front(const T &val);	//开头插入数据
		bool pop_front(T &val);	//开头删除数据
		void reverse();	//链表倒置
		bool del(const T & val);	//删除所有值为val 的元素
		bool erase(int s, int e);	//删除[s,e] 区间内容
		bool sort();	//从小到大排列，插入排序实现
		int count(const T & val);	//统计val 值出现的次数
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//返回元素个数
		void show() const;	//遍历链表
		T operator[](const int n) const;

	private:
		typedef struct _Node
		{
			T data;
			_Node * next;
		}Node;
		Node * head, * end;	//分别指向头结点、尾指针
		unsigned int _size;		//元素数
};
template<typename T>
List<T>::List()	//默认构造函数，创建头尾结点，元素数为0
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
	Node *temp = new Node;	//temp用作新尾,next属性设为head以循环(循环链表)
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
	val = temp->data;		//用于返回值
	head->next = temp->next;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return val;
}
template<typename T>
void List<T>::reverse()	//链表前端就地倒置
{
	if (_size < 2)
		return;
	Node * ps = head->next;	//新尾
	Node * pn = ps->next;	//从第二个结点开始未待倒置部分
	Node * pnn = pn->next;	//pnn标记待倒置部分
	while(pn != head)		//到结尾会循环到head
	{
		pn->next = head->next;	//pn融入已倒置部分
		head->next = pn;	//head带领已倒置部分
		pn = pnn;	
		pnn = pnn->next;	//未倒置部分后移
	}
	ps->next = head;	//ps指向的为已倒置部分最后一个结点，指向head保证循环
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
		Node * temp = pl;		//用于释放内存
		pl->next = head->next;
		while(pl != head)
		{
			if (pl->next->data == val)
			{
				temp = pl->next;	//存储待删位置
				pl->next = pl->next->next;	//隔离待删结点
				delete temp;	//释放内存
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
bool List<T>::erase(int s, int e) //删除[s,e]区间
{
	if (e<s || s<0 || e >= _size)
		return false;
	int num = s;
	Node * ps = head;
	while(num--)
		ps = ps->next;	//找到下标为s 的元素的前一个元素
	num = e - s + 1;			//释放e - s + 1 个元素
	Node * pe = ps->next;
	Node * pt = pe;
	while(num--)
	{
		pe = pe->next;
		delete pt;
		pt = pe;
	}
	ps->next = pe;		//拼接
	return true;
}


template<typename T>
bool List<T>::sort()	//插入排序算法
{
	if (_size >= 2)
	{
		Node * ps = head->next->next;	//指向未排序区域
		Node *pi, *pt;
		head->next->next = NULL;	//已排序区域(第一个结点)末尾设置NULL，以作标记
		while(ps != head)
		{
			for (pi = head; (pi->next != NULL) && (pi->next->data <= ps->data); pi = pi->next)	//查找插入位置
				continue;
			pt = ps;		//存取需插入节点
			ps = ps->next;		//未排序区后移
			if (pi->next != NULL)	//判断是否为已排序区最大值
			{
				pt->next = pi->next;
				pi->next = pt;
			}
			else
			{
				pi->next = pt;
				pt->next = NULL;	//为最大值需设置尾部NULL标记
			}
		}
		pt = head->next;	//寻找NULL前第一个节点
		while(pt->next)
			pt = pt->next;
		pt->next = head;	//循环
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
	std::cout <<"链表数据共" <<size() <<"个，内容如下:\n";
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
