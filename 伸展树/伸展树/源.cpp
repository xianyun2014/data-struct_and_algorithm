#include <iostream>

template <typename T>
class Splay_Tree
{
public:
	Splay_Tree();
	bool find(const T& val);
	void insert(const T& val);
	void del(const T& val);
private:
	typedef struct tagNODE
	{
		T data;
		struct tagNODE *left, *right;
		tagNODE(const T& val, tagNODE* cl, tagNODE* cr)
		{
			data = val;
			left = cl;
			right = cr;
		}
	}NODE;
	NODE *tree_root;

	NODE* own_find(NODE* tree, const T& val);
	NODE* rolatewithleft(NODE* tree);
	NODE* rolatewithright(NODE* tree);
};
template <typename T> Splay_Tree<T>::Splay_Tree()
{
	tree_root = NULL;
}
template <typename T> typename Splay_Tree<T>::NODE* Splay_Tree<T>::rolatewithleft(NODE* tree)
{
	NODE *p = tree->left;
	tree->left = p->right;
	p->right = tree;
	return p;
}
template <typename T> typename Splay_Tree<T>::NODE* Splay_Tree<T>::rolatewithright(NODE* tree)
{
	NODE *p = tree->right;
	tree->right = p->left;
	p->left = tree;
	return p;
}
template <typename T> typename Splay_Tree<T>::NODE* Splay_Tree<T>::own_find(NODE* tree, const T& val)
{
	if (NULL == tree)
		return tree;
	else if  (tree->data > val)
	{
		tree->left = own_find(tree->left, val);
		if (tree->left && tree->left->data == val)
			tree = rolatewithleft(tree);															
	}
	else if (tree->data < val)
	{
		tree->right = own_find(tree->right, val);
		if (tree->right && tree->right->data == val)
			tree = rolatewithright(tree);
	}
	return tree;
}

template <typename T> bool Splay_Tree<T>::find(const T& val)
{
	NODE *p = own_find(tree_root, val);
	if (NULL != p)
		tree_root = p;
	return p != NULL;
}
template <typename T> void Splay_Tree<T>::insert(const T& val)
{
	NODE *p = tree_root, *pr = NULL;
	NODE *pn = new NODE(val, NULL, NULL);
	while (p && p->data != val)
	{
		pr = p;
		if (val > p->data)
			p = p->right;
		else if (val < p->data)
			p = p->left;
	}
	if (NULL == tree_root)
		tree_root = pn;
	else if (NULL == p)
	{
		if (pr->data > val)
			pr->left = pn;
		else
			pr->right = pn;
	}
}
template <typename T> void Splay_Tree<T>::del(const T& val)
{
	if (NULL != own_find(tree_root, val))
	{
		NODE *pl = tree_root->left;
		NODE *pr = tree_root->right;
		delete tree_root;
		if (NULL != pl && NULL != pr)
		{
			pl->right = pr->left;
			pr->left = pl;
			tree_root = pr;
		}	
		else if (NULL == pl || NULL == pr)
			tree_root = (NULL == pl) ? pr : pl;
		else
			tree_root = NULL;
	}
}

int main()
{
	Splay_Tree<int> tree;
	for (int i = 1; i <= 5; ++i)
		tree.insert(i);
	tree.find(4);
	return 0;
}