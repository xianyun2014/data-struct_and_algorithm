template <typename T>
class RBTree
{
public:
	RBTree();
	//~RBTree();
	bool Insert(const T &val);
	bool Del(const T &val);
	void show() const {
		mid_order(root);
	}
	
private:
	enum { BLACK, RED };
	typedef struct tagNode
	{
		T data;
		bool color; // 0 black , 1 red
		struct tagNode *left, *right, *father;
	}Node;
	Node* search(const T &val)
	{
		Node *pr = root, *pf = nit;
		while (pr != nit)
		{
			pf = pr;
			if (pr->data > val){
				pr = pr->left;
			}
			else{
				pr = pr->right;
			}
		}
		return pf;
	}

	void mid_order(Node *)const;

	void fix_insert(Node *);
	void fix_del(Node *);
	void rotate_left(Node *);
	void rotate_right(Node *);
	Node *root, *nit;
};

template <typename T>
RBTree<T>::RBTree()
{
	nit = new Node;
	nit->color = BLACK;
	nit->father = nit->left = nit->right = nit;
	root = nit;
}
template <typename T>
void RBTree<T>::rotate_left(Node *p)
{
	Node *pc = p->right;
	pc->left->father = p;
	p->right = pc->left;

	if (p == p->father->left)
		p->father->left = pc;
	else
		p->father->right = pc;

	pc->father = p->father;
	p->father = pc;
	pc->left = p;
}

template <typename T>
void RBTree<T>::rotate_right(Node *p)
{
	Node *pc = p->left;
	pc->right->father = p;
	p->left = pc->right;

	if (p == p->father->left)
		p->father->left = pc;
	else
		p->father->right = pc;

	pc->father = p->father;
	p->father = pc;
	pc->right = p;
}

template <typename T>
bool RBTree<T>::Insert(const T &val)
{
	Node *tmp = new Node;
	tmp->color = RED;
	tmp->data = val;
	tmp->left = tmp->right = nit;

	Node *pf = search(val);

	if (pf == nit)
	{
		root = tmp;
		tmp->left = tmp->right = tmp->father = nit;
	}
	else
	{
		tmp->father = pf;
		if (pf->data > tmp->data)
			pf->left = tmp;
		else
			pf->right = tmp;
		
		fix_insert(tmp);
	}
	return true;
}

template <typename T>
void RBTree<T>::fix_insert(Node *p)
{
	Node *pf = p->father;
	Node *pu;
	while (p->father->color == RED)
	{
		if (pf == pf->father->left)
			pu = pf->father->right;
		else
			pu = pf->father->left;

		if (pu->color == RED)
		{
			pf->color = BLACK;
			pu->color = BLACK;
			pf->father->color = RED;
			p = pf->father;
		}
		else
		{
			pf->father->color = RED;
			pf->color = BLACK;
			if (pf == pf->father->left)
				rotate_right(pf->father);
			else
				rotate_left(pf->father);
		}
	}
}

template <typename T>
void RBTree<T>::mid_order(Node *root) const
{
	if (root != nit)
	{
		mid_order(root->left);
		std::cout << root->data <<" " << root->color << std::endl;
		mid_order(root->right);
	}
}

template <typename T>
bool RBTree<T>::Del(const T &val)
{
	Node *pf = search(val);
	if (pf == nit)
		return false;

	if (pf->left != nit && pf->right != nit)
	{
		Node *pc = pf->right;
		while (pc->left != nit)
			pc = pc->left;

		std::swap(pc->data, pf->data);
		pf = pc;
	}
	if (pf->left != nit)
		pf->right = pf->left;

	pf->right->father = pf->father;
	if (pf == pf->father->left)
		pf->father->left = pf->right;
	else
		pf->father->right = pf->right;

	if (pf->color == BLACK)
		fix_del(pf->right);

	delete pf;
	return true;
}

template <typename T>
void RBTree<T>::fix_del(Node * p)
{
	Node *pb;
	while (p != root && p->color == RED)
	{
		if (p == p->father->left)
		{
			pb = p->father->right;
			if (pb->color == RED)
			{
				pb->color = BLACK;
				p->father->color = RED;
				rotate_left(p->father);
				pb = p->father->right;
			}
		}
		else
		{
			pb = p->father->left;
			if (pb->color == RED)
			{
				pb->color = BLACK;
				p->father->color = RED;
				rotate_right(p->father);
				pb = p->father->left;
			}
		}
		if (pb->left->color == BLACK && pb->right->color == BLACK)
		{
			pb->color = RED;
			p = p->father;
		}
		else
		{
			if (pb->left->color == RED)
			{
				pb->left->color = BLACK;
				pb->color = RED;
				rotate_right(pb);
				pb = pb->father;
			}
			pb->color = pb->father->color;
			pb->father->color = BLACK;
			rotate_left(pb->father);
			p = root;
		}
	}
	p->color = BLACK;
}