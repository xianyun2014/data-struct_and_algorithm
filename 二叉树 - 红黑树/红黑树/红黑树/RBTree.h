#include <iostream>

template <typename T>
class RBTree
{
public:
	RBTree();
	bool insert(const T&);
	bool del(const T&);
	void show() { 
		Mid_Order(root);
	}
	
private:
	
	enum { RED, BLACK };
	
typedef struct _node
	{
		bool color;
		T data;
		struct _node * p, *left, *right;
	}Node;

	Node *root;
	Node *nil;
	unsigned int Size;
	
	void RB_Ins_Fix(Node *);
	void RB_Del_Fix(Node *);
	void Left_Rotate(Node *);
	void Right_Rotate(Node *);

	void Replace(Node *, Node *);
	void Mid_Order(const Node *);
};

template <typename T>
RBTree<T>::RBTree()
{
	Node *p = new Node;
	Size = 0;
	nil = new Node;
	nil->color = BLACK;
	nil->p = nil->left = nil->right = NULL;
	root = nil;
}

template <typename T>
bool RBTree<T>::insert(const T& val)
{
	Node *pf = nil;
	Node *pc = root;
	while (pc != nil)
	{
		pf = pc;
		if (val >= pc->data)
			pc = pc->right;
		else
			pc = pc->left;
	}
	Node *pn = new Node;
	pn->data = val;
	pn->p = pf;
	pn->left = pn->right = nil;
	pn->color = RED;
	if (pf == nil)
	{
		pn->color = BLACK;
		root = pn;
		return true;
	}
	else
	{
		if (val >= pf->data)
			pf->right = pn;
		else
			pf->left = pn;
	}
	RB_Ins_Fix(pn);
	return true;
}

template <typename T>
void RBTree<T>::RB_Ins_Fix(Node * ps)
{
	while (ps->p->color == RED)
	{
		Node * pb;
		if (ps->p == nil)
			return;
		
		if (ps->p == ps->p->p->left)
			pb = ps->p->p->right;
		else
			pb = ps->p->p->left;
		if (pb->color == RED)
		{
			pb->color = BLACK;
			ps->p->color = BLACK;
			ps->p->p->color = RED;
			ps = ps->p->p;
		}
		else
		{
			if (ps == ps->p->right && ps->p == ps->p->p->left)
			{
				Left_Rotate(ps->p);
				ps = ps->left;
			}
			else if (ps == ps->p->left && ps->p == ps->p->p->right)
			{
				Right_Rotate(ps->p);
				ps = ps->right;
			}
			ps->p->color = BLACK;
			ps->p->p->color = RED;
			if (ps == ps->p->right && ps->p == ps->p->p->right)
				Left_Rotate(ps->p->p);
			else
				Right_Rotate(ps->p->p);
		}
	}
	root->color = BLACK;
	
}

template <typename T>
void RBTree<T>::Left_Rotate(Node * pf)
{
	Node * pc = pf->right;
	pc->p = pf->p;
	if (pf->p != nil)
	{
		if (pf == pf->p->left)
			pf->p->left = pc;
		else
			pf->p->right = pc;
	}
	pf->right = pc->left;
	if (pf == root)
		root = pc;
	if (pc->left != nil)
		pc->left->p = pf;
	pc->left = pf;
	pf->p = pc;
}

template <typename T>
void RBTree<T>::Right_Rotate(Node * pf)
{
	Node * pc = pf->left;
	pc->p = pf->p;
	if (pf->p != nil)
	{
		if (pf == pf->p->left)
			pf->p->left = pc;
		else
			pf->p->right = pc;
	}
	pf->left = pc->right;
	if (pf == root)
		root = pc;
	if (pc->right != nil)
		pc->right->p = pf;
	pc->right = pf;
	pf->p = pc;
}


template <typename T>
void RBTree<T>::Mid_Order(const Node *p)
{
	if (p != nil)
	{
		Mid_Order(p->left);
		std::cout << "结点" << p->data << " " << ((p->color) ? "黑" : "红") << endl;
		Mid_Order(p->right);
	}
}


template <typename T>
bool RBTree<T>::del(const T& val)
{	
	Node *pc = nil;
	Node *pn = root;
	while (pn != nil && pc->data != val)
	{
		pc = pn;
		if (val >= pn->data)
			pn = pn->right;
		else
			pn = pn->left;
	}
	if (pc == nil || pc->data != val)
		return false;

	if (pc->color == RED)
	{
		if (pc == pc->p->left)
			pc->p->left = nil;
		else
			pc->p->right = nil;
		delete pc;
	}
	else
	{
		Node *pt = pc; //寻找右侧结点
		if (pt->right != nil)
			while (pt->left != nil)
				pt = pt->left;
		if (pt != pc)
			Replace(pt, pc); //交换结点，转换为删除单子树结点问题

		pc = pt;
		pt = pt->right;
		pc->p->left = pt;
		pt->p = pc->p;
		if (pc == root)
			root = pt;
		delete pc;
		RB_Del_Fix(pt);
	}
	return true;
}

template <typename T>
void RBTree<T>::RB_Del_Fix(Node *x)
{
	while (x != root && x->color == BLACK)
	{
		Node *w;
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				w->p->color = RED;
				Left_Rotate(w->p);
				w = x->p->right;
			}
		}
		else
		{
			w = x->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				w->p->color = RED;
				Right_Rotate(w->p);
				w = x->p->left;
			}
		}
		if (w->left->color == BLACK && w->right->color == BLACK)
		{
			w->color = RED;
			x = x->p;
		}
		else
		{
			if (w->left->color == RED)
			{
				w->left->color = BLACK;
				w->color = RED;
				Right_Rotate(w);
				w = w->p;
			}
			w->color = w->p->color;
			w->p->color = BLACK;
			w->right->color = BLACK;
			Left_Rotate(w->p);
			x = root; //已经平衡，退出
		}
	}
	x->color = BLACK;
}

template <typename T>
void RBTree<T>::Replace(Node *x, Node *y)
{
	/*
	Node *tmp;

	if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;

	tmp = x->p;
	x->p = y->p;
	y->p = tmp; 

	tmp = x->left;
	x->left = y->left;
	y->left = tmp;

	tmp = x->right;
	x->right = y->right;
	y->right = tmp;

	if (x->color != y->color)
	{
		if (x->color == RED)
		{
			x->color = BLACK;
			y->color = RED;
		}
		else
		{
			x->color = RED;
			y->color = BLACK;
		}
	}
	*/
	T t = x->data;
	x->data = y->data;
	y->data = t;
}