/********************************************************************
    purpose:    线性开型寻址散列
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/23
*********************************************************************/

template<typename K, typename T> class hashtable;

template<typename K, typename T>
class node
{
	friend hashtable<K,T>;
	operator K() {return k;}
	private:
		K k;
		T data;
};
template<typename K, typename T>
class hashtable
{
	public:
		hashtable(int num);
		~hashtable();
		bool search(const K k);
		bool insert(K k, const T val);
		bool del(K k);
		void show()const;
	private:
		int hsearch(K k);
		int D;
		node<K,T> *ht;
		bool *empty;
};
template<typename K, typename T>
hashtable<K,T>::hashtable(int num)
{
	D = num; 
	ht = new node<K,T> [D];
	empty = new bool [D];
	for (int i = 0; i < D; i++)
		empty[i] = true;
}
template<typename K, typename T>
hashtable<K,T>::~hashtable()
{
	delete [] ht;
	delete [] empty;
}
template<typename K, typename T>
int hashtable<K,T>::hsearch(K k)
{
	int i = k % D;
	int t = i;
	do
	{
		if (empty[t] || ht[t].k == k)
			return t;
		t = (t+1) % D;
	}while (t != i);
	return t;
}
template<typename K, typename T>
bool hashtable<K,T>::search(const K k)
{
	int i = hsearch(k);
	if (empty[i] || ht[i].k != k)
		return false;
	else 
		return true;
}
template<typename K, typename T>
bool hashtable<K,T>::insert(K k, const T val)
{
	int i = hsearch(k);
	if (empty[i])
	{
		empty[i] = false;
		ht[i].data = val;
		ht[i].k = k;
		return true;
	}
	return false;	
}
template<typename K, typename T>
bool hashtable<K,T>::del(K k)
{
	int i = hsearch(k);
	if (ht[i].k != k)
		return false;
	empty[i] = true;
	return true;
}
template<typename K, typename T>
void hashtable<K,T>::show() const
{
	for (int i = 0; i < D; ++i)
	{
		if (!empty[i])
			std::cout <<ht[i].data <<"  ";
	}
	std::cout <<std::endl;
}