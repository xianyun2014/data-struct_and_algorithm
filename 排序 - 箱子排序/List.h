/********************************************************************
    purpose:    ��������
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/17
	explain:
			�ɼ���0~6��ɣ�����ʱ������7������
*********************************************************************/

#include <iostream>


template<typename T>  //��ͷ���ĵ�����ʵ�ּ򵥶������ڲ���ɾ��
class List
{
	public:
		List();
		~List();
		bool push(const T &val);	//ĩβ��������
		bool pop(T &val);	//��ͷɾ������
		void append(List<T> &lst);
		bool empty(){return _size == 0;}
		unsigned int size() const {return _size;}	//����Ԫ�ظ���
		void show() const;	//��������
	private:
		typedef struct Nodestruct
		{
			T data;
			Nodestruct * next;
		}Node;
		Node * head, * end;	//�ֱ�ָ��ͷ��㡢βָ��
		unsigned int _size;		//Ԫ����
};
template<typename T>
List<T>::List()	//Ĭ�Ϲ��캯��������ͷβ��㣬Ԫ����Ϊ0
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
	end = temp;		//ָ����β
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
	std::cout <<"���ݹ�" <<size() <<"������������:\n";
	while(temp != NULL){
		std::cout <<temp->data <<std::endl;
		temp = temp->next;
	}
}



class stu	//���ڴ洢�ɼ�������
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

void binsort(List<stu> &a, int range)		//���������㷨
{
	int len = a.size();
	List<stu> * bin;
	bin = new List<stu> [range + 1];	//��������
	stu temp;
	for (int i = 0; i < len; ++i)		//��������
	{
		a.pop(temp);
		bin[temp.score].push(temp);
	}
	for (int j = 0; j <= range; ++j)	//�ռ�����
		if (!bin[j].empty())
			a.append(bin[j]);
}