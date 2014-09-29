//avl_tree.h
#include <stack>
using std::stack;

template <typename T>
class AVL_TREE
{
public:
	AVL_TREE(){
		nil = new AVL_NODE(0, -1, NULL, NULL);
		tree_root = nil;
	}
	bool find(const T &val) const;
	void insert(const T &val);
	void del(const T &val);//¶èÐÔÉ¾³ý

	typedef struct tagAVL_NODE
	{
		bool exist;
		T data;
		int height;
		struct tagAVL_NODE *left, *right;
		tagAVL_NODE(const T &val, int wg, tagAVL_NODE *cl, tagAVL_NODE *cr){
			data = val;
			height = wg;
			left = cl;
			right = cr;
			exist = 1;
		}
	}AVL_NODE;

private:
	AVL_NODE* tree_root, * nil;
	AVL_NODE* own_insert(AVL_NODE* tree, const T &val);
	AVL_NODE* rolatewithleft(AVL_NODE *p);
	AVL_NODE* rolatewithright(AVL_NODE *p);
};
template <typename T> bool AVL_TREE<T>::find(const T &val) const
{
	AVL_NODE *p = tree_root;
	while (p != nil && p->data != val)
	{
		if (p->data < val)
			p = p->right;
		else if (p->data > val)
			p = p->left;
	}
	return p != nil && p->data == val && p->exist;
}
template <typename T> typename AVL_TREE<T>::AVL_NODE* AVL_TREE<T>::rolatewithleft(AVL_NODE *p)
{
	AVL_NODE *h = p->left;
	p->left = h->right;
	h->right = p;
	p->height = p->left->height > p->right->height ? p->left->height + 1 : p->right->height + 1;
	h->height = h->left->height > h->right->height ? h->left->height + 1 : h->right->height + 1;
	return h;
}
template <typename T> typename AVL_TREE<T>::AVL_NODE* AVL_TREE<T>::rolatewithright(AVL_NODE *p)
{
	AVL_NODE *h = p->right;
	p->right = h->left;
	h->left = p;
	p->height = p->left->height > p->right->height ? p->left->height + 1 : p->right->height + 1;
	h->height = h->left->height > h->right->height ? h->left->height + 1 : h->right->height + 1;
	return h;
}
/*   
template <typename T> void AVL_TREE<T>::insert(const T &val)
{
	AVL_NODE *p = tree_root;
	stack<AVL_NODE*> st;
	while (p != nil && p->data != val)
	{
		st.push(p);
		if (p->data < val)
			p = p->right;
		else if (p->data > val)
			p = p->left;
	}
	if (p == nil)
	{
		AVL_NODE *pn = new AVL_NODE(val, 0, nil, nil);
		if (tree_root == nil)
			tree_root = pn;
		else
		{
			AVL_NODE * pt = st.top();
			if (pt->data > val)
				pt->left = pn;
			else
				pt->right = pn;

			if (pt->height == 0)
				++pt->height;
			else
				return;//ÒÑÆ½ºâ
			
			AVL_NODE *pf, *pgf, *tmp_f;
			while (!st.empty())
			{
				pf = st.top();
				st.pop();
				if (st.empty())
					return;
				pgf = st.top();
				st.pop();

				pf->height = pf->left->height > pf->right->height ? pf->left->height + 1 : pf->right->height + 1;
				pgf->height = pgf->left->height > pgf->right->height ? pgf->left->height + 1 : pgf->right->height + 1;

				if (abs(pgf->left->height - pgf->right->height) >= 2)
				{
					if (pn == pf->left && pf == pgf->left)
						tmp_f = rolatewithleft(pgf);
					else if (pn == pf->right && pf == pgf->right)
						tmp_f = rolatewithright(pgf);
					else if (pn == pf->left && pf == pgf->right)
					{
						pgf->right = rolatewithleft(pf);
						tmp_f = rolatewithright(pgf);
					}
					else if (pn == pf->right && pt == pgf->left)
					{
						pgf->left = rolatewithright(pf);
						tmp_f = rolatewithleft(pgf);
					}

					if (st.empty())
						tree_root = tmp_f;
					else
					{
						if (st.top()->left == pgf)
							st.top()->left = tmp_f;
						else
							st.top()->right = tmp_f;
					}
					if (tmp_f->left != nil)
						pn = tmp_f->left;
					else
						pn = tmp_f->right;
					st.push(tmp_f);
				}
				else
				{
					pn = pf;
					st.push(pgf);
				}
			}
		}
	}
}
*/
template <typename T> void AVL_TREE<T>::insert(const T &val)
{
	AVL_NODE *p = own_insert(tree_root, val);
	if (tree_root == nil)
	{
		tree_root = p;
	}
	else if (p->left == tree_root || p->right == tree_root)
		tree_root = p;
}
template <typename T> typename AVL_TREE<T>::AVL_NODE* AVL_TREE<T>::own_insert(AVL_NODE* tree, const T &val)
{
	if (nil == tree)
		tree = new AVL_NODE(val, 0, nil, nil);
	else if (val > tree->data)
	{
		tree->right = own_insert(tree->right, val);
		if (2 == tree->right->height - tree->left->height)
		{
			if (val > tree->right->data)
				tree = rolatewithright(tree);
			else
			{
				tree->right = rolatewithleft(tree->right);
				tree = rolatewithright(tree);
			}
		}
	}
	else if (val < tree->data)
	{
		tree->left = own_insert(tree->left, val);
		if (2 == tree->left->height - tree->right->height)
		{
			if (val < tree->right->data)
				tree = rolatewithleft(tree);
			else
			{
				tree->left = rolatewithright(tree->left);
				tree = rolatewithleft(tree);
			}
		}
	}
	else //val == tree->data
	{
		tree->exist = 1;
	}
	if (tree != nil) tree->height = (tree->right->height > tree->left->height ? tree->right->height : tree->left->height) + 1;
	return tree;
}
template <typename T> void AVL_TREE<T>::del(const T &val)
{
	AVL_NODE *p = tree_root;
	while (p != nil && p->data != val)
	{
		if (p->data < val)
			p = p->right;
		else if (p->data > val)
			p = p->left;
	}
	if (p != nil && p->data == val)
		p->exist = 0;
}