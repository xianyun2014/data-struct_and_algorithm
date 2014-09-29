/********************************************************************
    purpose:    ����
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/23
*********************************************************************/

#include <cmath>
#include <ctime>

template<typename K, typename T>
class skiplist
{
private:
	typedef struct _node
	{
		K key;
		T data;
		struct _node **link;	//�洢�༶��
	}node;
	node *head, *tail, **last;//last�����ڲ����ɾ��ʱ�ò��Һ����洢������λ�õ�ǰ����������ָ��
	int MaxLevel, Levels, CutOff;	//�������������ǰ����������ȷ�������������ֵ
	K Large;	//���ܴ洢���������ֵ
	node* savesearch(const K& val);	//����ֵ��ȷ��last
	int level();	//�����ȡ������
public:
	skiplist(K MaxValue, int maxnum);	//���ܴ洢���������ֵ������ȷ���������������ܸ����ο�ֵ
	~skiplist();
	bool insert(const K& k, const T& val);
	bool del(const K& k);
	void show() const;
};
template<typename K, typename T>
skiplist<K,T>::skiplist(K MaxValue, int maxnum)
{
    MaxLevel = log(maxnum)/log(2) - 1;
    Levels = 0;
	Large = MaxValue;
    CutOff = RAND_MAX/2; //Ϊ��һ�����ĸ���Ϊ1/2
    srand(time(0));
    head = new node;
    head->link = new node *[MaxLevel + 1];	//�������м���
    tail = new node;
	tail->key = Large;
    tail->link = new node *[0]; //βָ�벻��Ҫ����
    last = new node *[MaxLevel + 1];	//���ڴ洢�������������λ��
    for (int i = 0; i <= MaxLevel; ++i) //��ʼȫ��Ϊtail����Ϊ��
	    head->link[i] = tail;
}
template<typename K, typename T>
skiplist<K,T>::~skiplist()
{
    node *tmp = head;
    while(tmp != tail)
    {
		head = head->link[0]; //��0�����ͷ�
		delete [] tmp->link;
		delete tmp;
		tmp = head;
    }
    delete [] last;
}
template<typename K, typename T>
int skiplist<K,T>::level()
{
    int lev = 0;
    while (rand() <= CutOff)//�����ȡ����
		lev++;
    return (lev > MaxLevel)? MaxLevel : lev;;
}
template<typename K, typename T>
skiplist<K,T>::node* skiplist<K,T>::savesearch(const K& val)
{
	node *tmp = head;
	for (int i = Levels; i >= 0; --i)//Ѱ��ǰһλ��
	{
		while (tmp->link[i]->key < val)
			tmp = tmp->link[i];
		last[i] = tmp; //�洢������ǰһλ��
	}
	return (tmp->link[0]);//���ز���λ��
}
template<typename K, typename T>
bool skiplist<K,T>::insert(const K& k, const T& val)
{
	if (k >= Large)	//����������ֵ
		return false;
	node* tmp = savesearch(k);
	if (tmp->key == k)	// ���д����ݲ��ٲ���
		return false;
	int lev = level();
	if (lev > Levels) //���⼶��
	{
		lev = ++Levels;
		last[lev] = head;
	}
	node* p = new node;
	p->link = new node *[lev + 1];
	p->key = k;
	p->data = val;
	for (int i = 0; i <= lev; ++i) //����
	{
		p->link[i] = last[i]->link[i];
		last[i]->link[i] = p;
	}
	return true;
}
template<typename K, typename T>
bool skiplist<K,T>::del(const K& k)
{
	if (k >= Large)
		return false;
	node* tmp = savesearch(k);
	if (tmp->key != k) //�޴�������
		return false;
	for (int i = 0; i <= Levels && last[i]->link[i] == tmp; ++i) //* ɾ��
		last[i]->link[i] = tmp->link[i];
	delete [] tmp->link; //�ͷ�
	delete tmp;
	while (Levels > 0 && head->link[Levels] == tail) //���⼶��
		Levels--;
	return true;
}
template<typename K, typename T>
void skiplist<K,T>::show() const
{
	node* tmp = head->link[0];
	std::cout <<"key:" <<"\t" <<"data:" <<std::endl <<"------------------\n";
	while (tmp != tail)
	{
		std::cout <<tmp->key <<"\t" <<tmp->data <<std::endl;
		tmp = tmp->link[0];
	}
	if (head->link[0] != tail) //������Ϊ��ʱ�������
		std::cout <<std::endl;
}