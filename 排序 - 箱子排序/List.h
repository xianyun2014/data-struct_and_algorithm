/********************************************************************
    purpose:    箱子排序
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/17
	explain:
			成绩由0~6组成，排序时可生成7个箱子
*********************************************************************/

#include <iostream>


template<typename T>  //带头结点的单链表实现简单队列用于插入删除
class List
{
	public:
		List();
		~List();
		bool push(const T &val);	//末尾插入数据
		bool pop(T &val);	//开头删除数据
		void append(List<T> &lst);
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//返回元素个数
		void show() const;	//遍历链表
	private:
		typedef struct Nodestruct
		{
			T data;
			Nodestruct * next;
		}Node;
		Node * head, * end;	//分别指向头结点、尾指针
		unsigned int _size;		//元素数
};
template<typename T>
List<T>::List()	//默认构造函数，创建头尾结点，元素数为0
{
	_size = 0;
	head = new Node;
	head->next = NULL;
	end = head;
}
template<typename T>
List<T>::~List()
{
	Node * ph = head, *pt = head->next;
	while(pt != NULL)
	{
		ph = pt->next;
		delete pt;
		pt = ph;
	}
}
template<typename T>
bool List<T>::push(const T & val)
{
	Node *temp = new Node;
	temp->data = val;
	temp->next = NULL;
	end->next = temp;
	end = temp;		//指向新尾
	++_size;
	return true;
}

template<typename T>
bool List<T>::pop(T & val)
{
	if (_size == 0)
		return false;
	Node *temp = head->next;
	val = temp->data;
	head->next = temp->next;
	delete temp;
	--_size;
	if (_size == 0)
		end = head;
	return true;
}
template<typename T>
void List<T>::append(List<T> & lst)
{
	if (lst._size == 0)
		return;
	end->next = lst.head->next;
	end = lst.end;
	_size += lst._size;
}	
template<typename T>
void List<T>::show()const
{
	Node * temp = head->next;
	std::cout <<"数据共" <<size() <<"个，内容如下:\n";
	while(temp != NULL){
		std::cout <<temp->data <<std::endl;
		temp = temp->next;
	}
}



class stu	//用于存储成绩、姓名
{
	friend std::ostream& operator << (std::ostream&, const stu &);
	friend void binsort(List<stu> &a, int range);
public:
	void set(int s, char *str){score = s; name = str;}
	operator int()const {return score;}
private:
	int score;
	char * name;
};
std::ostream& operator<< (std::ostream& os, const stu &val)
{
	os <<val.score <<"  " <<val.name <<" ";
	return os;
}

void binsort(List<stu> &a, int range)		//箱子排序算法
{
	int len = a.size();
	List<stu> * bin;
	bin = new List<stu> [range + 1];	//创建箱子
	stu temp;
	for (int i = 0; i < len; ++i)		//放入箱子
	{
		a.pop(temp);
		bin[temp.score].push(temp);
	}
	for (int j = 0; j <= range; ++j)	//收集数据
		if (!bin[j].empty())
			a.append(bin[j]);
}