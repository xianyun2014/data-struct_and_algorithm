/********************************************************************
    purpose:    二叉排序树
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/25
	explain:
		按层遍历中使用了List 保存指针
*********************************************************************/


#include <iostream>
#include "List.h"

template <typename T>
class binarytree
{
	public:
		binarytree(T initval);
		~binarytree();
		void insert(const T val);
		int high() {return treehigh(tree);}
		int number() {return treenumber(tree);}
		bool find(const T val);
		void preorder() {::PreOrder(tree);}
		void inorder() {::InOrder(tree);}
		void postorder() {::PostOrder(tree);}
		void levelorder() {::LevelOrder(tree);}
	private:
		typedef struct _treenode
		{
			T data;
			struct _treenode *left, *right;
		}treenode;
		friend class queue;
		friend void PreOrder(binarytree<T>::treenode *tnode);
		friend void InOrder(binarytree<T>::treenode *tnode);
		friend void PostOrder(binarytree<T>::treenode *tnode);
		friend void LevelOrder(binarytree<T>::treenode *tnode);
		friend void delbinary(treenode *tnode);
		friend int main();
		treenode *tree;
};
template <typename T> int treehigh(binarytree<T>::treenode *tnode);
template <typename T> int treenumber(binarytree<T>::treenode *tnode);

template <typename T>
binarytree<T>::binarytree(T initval)
{
	tree = new treenode;
	tree->data = initval;
	tree->left = tree->right = NULL;
}
template <typename T>
binarytree<T>::~binarytree()
{
	delbinary(tree);
}
template <typename T>
void delbinary(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		if (tnode->left)
			delbinary(tnode->left);
		if (tnode->right)
			delbinary(tnode->right);
	}
}
template <typename T>
void binarytree<T>::insert(const T val)
{
	treenode *tmp = new treenode;
	tmp->data = val;
	tmp->left = tmp->right = NULL;
	treenode *pt = tree;
	while (pt)
	{
		if (val < pt->data)
		{
			if (pt->left != NULL)
				pt = pt->left;
			else
			{
				pt->left = tmp;
				break;
			}
		}
		else
		{
			if (pt->right != NULL)
				pt = pt->right;
			else
			{
				pt->right = tmp;
				break;
			}
		}
	}
}
template <typename T>
bool binarytree<T>::find(const T val)
{
	treenode *pt = tree;
	while (pt)
	{
		if (pt->data == val)
			return true;
		if (val < pt->data)
			pt = pt->left;
		else
			pt = pt->right;
	}
	return false;
}
template <typename T>
void PreOrder(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		Visit(tnode);
		PreOrder(tnode->left);
		PreOrder(tnode->right);
	}
}
template <typename T>
void InOrder(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		InOrder(tnode->left);
		Visit(tnode);
		InOrder(tnode->right);
	}
}
template <typename T>
void PostOrder(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		PostOrder(tnode->left);
		PostOrder(tnode->right);
		Visit(tnode);
	}
}
template <typename T>
void LevelOrder(binarytree<T>::treenode *tnode)
{
	List<binarytree<T>::treenode*> que;
	while (tnode)
	{  
		Visit(tnode);
		if (tnode->left)
			que.push_back(tnode->left);
		if (tnode->right)
			que.push_back(tnode->right);
		if (que.empty())
			break;
		que.pop_front(tnode);
	}
}
template <typename T>
void Visit(binarytree<T>::treenode *tnode)
{
	std::cout <<tnode->data <<" ";
}

template <typename T> int treehigh(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		int l = treehigh(tnode->left) + 1;
		int r = treehigh(tnode->right) + 1;
		return (l > r)? l : r;
	}
	return 0;
}
template <typename T> int treenumber(binarytree<T>::treenode *tnode)
{
	if (tnode)
	{
		return treenumber(tnode->left) + treenumber(tnode->right) + 1;
	}
	return 0;
}