/********************************************************************
    purpose:    ¡¥±Ì…¢¡–
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/23
*********************************************************************/
template<typename K, typename T>
class hashlist
{
	public:
		hashlist(int num);
		~hashlist();
		bool search(const K k, T& val);
		bool insert(const K k, T val);
		bool del(const K k);
		void show()const;
	private:
		typedef struct _node
		{
			K key;
			T data;
			struct _node *next;
		}node;
		node* hsearch(K k);
		int D;
		node **lst;
};
template<typename K, typename T>
hashlist<K,T>::hashlist(int num)
{
	D = num; 
	lst = new node *[D];
	for (int i = 0; i < D; i++)
	{
		lst[i] = new node;
		lst[i]->next = NULL;
	}
}
template<typename K, typename T>
hashlist<K,T>::~hashlist()
{
	node *tmp, *ph;
	for (int i = 0; i < D; ++i)
	{
		tmp = lst[i]->next;
		while (tmp)
		{
			ph = tmp->next;
			delete tmp;
			tmp = ph;
		}
		delete lst[i];
	}
	delete lst;
}
template<typename K, typename T>
hashlist<K,T>::node* hashlist<K,T>::hsearch(K k)
{
	node *tmp = lst[k % D];
	while(tmp->next) 
	{
		if (tmp->next->key == k)
			return tmp;
		tmp = tmp->next;
	}
	return tmp;
}
template<typename K, typename T>
bool hashlist<K,T>::search(const K k, T& val)
{
	node* pt = hsearch(k);
	if (pt->next == NULL)
		return false;
	if (pt->next->key == k)
	{
		val = pt->next->data;
		return true;
	}
	else 
		return false;
}
template<typename K, typename T>
bool hashlist<K,T>::insert(const K k,T val)
{
	node* pt = hsearch(k);
	if (pt)
	{
		node* tmp = new node;
		tmp->key = k;
		tmp->data = val;
		tmp->next = pt->next;
		pt->next = tmp;
		return true;
	}
	return false;
}
template<typename K, typename T>
bool hashlist<K,T>::del(const K k)
{
	node* pt = hsearch(k);
	if (pt->next != NULL)
	{
		node* tmp = pt->next;
		pt->next = tmp->next;
		delete tmp;
		if (pt == lst[k%D])
			pt->next = NULL;
		return true;
	}
	return false;
}
template<typename K, typename T>
void hashlist<K,T>::show() const
{
	node* tmp;
	for (int i = 0; i < D; ++i)
	{
		tmp = lst[i]->next;
		while (tmp)
		{
			std::cout <<tmp->data <<"  ";
			tmp = tmp->next;
		}
	}
	std::cout <<std::endl;
}
