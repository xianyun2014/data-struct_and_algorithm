/********************************************************************
    purpose:    跳表
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
		struct _node **link;	//存储多级链
	}node;
	node *head, *tail, **last;//last用于在插入或删除时用查找函数存储待作用位置的前面各级链表的指针
	int MaxLevel, Levels, CutOff;	//最大链表级数、当前级数、用于确定随机链表级数的值
	K Large;	//所能存储的数据最大值
	node* savesearch(const K& val);	//查找值并确定last
	int level();	//随机获取链表级数
public:
	skiplist(K MaxValue, int maxnum);	//所能存储的数据最大值，用于确定链表级数的数据总个数参考值
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
    CutOff = RAND_MAX/2; //为下一级链的概率为1/2
    srand(time(0));
    head = new node;
    head->link = new node *[MaxLevel + 1];	//分配所有级数
    tail = new node;
	tail->key = Large;
    tail->link = new node *[0]; //尾指针不需要级数
    last = new node *[MaxLevel + 1];	//用于存储各级链表的需用位置
    for (int i = 0; i <= MaxLevel; ++i) //初始全部为tail，即为空
	    head->link[i] = tail;
}
template<typename K, typename T>
skiplist<K,T>::~skiplist()
{
    node *tmp = head;
    while(tmp != tail)
    {
		head = head->link[0]; //沿0级链释放
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
    while (rand() <= CutOff)//随机获取级数
		lev++;
    return (lev > MaxLevel)? MaxLevel : lev;;
}
template<typename K, typename T>
skiplist<K,T>::node* skiplist<K,T>::savesearch(const K& val)
{
	node *tmp = head;
	for (int i = Levels; i >= 0; --i)//寻找前一位置
	{
		while (tmp->link[i]->key < val)
			tmp = tmp->link[i];
		last[i] = tmp; //存储所有链前一位置
	}
	return (tmp->link[0]);//返回查找位置
}
template<typename K, typename T>
bool skiplist<K,T>::insert(const K& k, const T& val)
{
	if (k >= Large)	//大于最大接受值
		return false;
	node* tmp = savesearch(k);
	if (tmp->key == k)	// 已有此数据不再插入
		return false;
	int lev = level();
	if (lev > Levels) //调解级数
	{
		lev = ++Levels;
		last[lev] = head;
	}
	node* p = new node;
	p->link = new node *[lev + 1];
	p->key = k;
	p->data = val;
	for (int i = 0; i <= lev; ++i) //插入
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
	if (tmp->key != k) //无此数据项
		return false;
	for (int i = 0; i <= Levels && last[i]->link[i] == tmp; ++i) //* 删除
		last[i]->link[i] = tmp->link[i];
	delete [] tmp->link; //释放
	delete tmp;
	while (Levels > 0 && head->link[Levels] == tail) //调解级数
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
	if (head->link[0] != tail) //本来不为空时输出换行
		std::cout <<std::endl;
}