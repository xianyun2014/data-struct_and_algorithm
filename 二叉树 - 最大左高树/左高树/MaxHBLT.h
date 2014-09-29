
#include <iostream>


template <typename T>
inline void Swap(T& a, T& b)
{
	T c = a;
	a = b; 
	b = c;
}
template <typename T> class MaxHBLT;

template <typename T>
class TNode
{
	friend MaxHBLT<T>;
public:
	TNode(const T& val)
	{
		data = val;
		s = 1;
		left = right = 0;
	}
private:
	T data;
	unsigned int s;
	TNode<T> *left, *right;
};

template <typename T>
class MaxHBLT
{
public:
	MaxHBLT();
	bool meld(TNode<T> *&rl, TNode<T> *rr);
	bool insert(const T& val);
	unsigned int high() const { return root->s;}
	void show() const {h_show(root);}
	bool del(T& val);
private:
	void h_show(TNode<T> *node) const;

	TNode<T> *root;
};

template <typename T>
MaxHBLT<T>::MaxHBLT()
{
	root = 0;
}
template <typename T>
bool MaxHBLT<T>::meld(TNode<T> *&rl, TNode<T> *rr)
{
	if (!rr)
		return false;
	if (!rl)
	{
		rl = rr;
		return true;
	}
	if (rl->data < rr->data)
		Swap(rl, rr);
	meld(rl->right, rr);
	if (!rl->left)
	{
		rl->left = rl->right;
		rl->right = 0;
		rl->s = 1;
	}
	else
	{
		if (rl->left->s < rl->right->s )
			Swap(rl->left, rl->right);
		rl->s = rl->right->s + 1;
	}
	return true;
}

template <typename T>
bool MaxHBLT<T>::insert(const T& val)
{
	TNode<T> *ps = new TNode<T> (val);
	return meld(root, ps);
}

template <typename T>
bool MaxHBLT<T>::del(T& val)
{
	if (!root)
		return false;
	val = root->data;
	if ( ! meld(root->left, root->right))
		return false;
	TNode<T> *p = root;
	root = root->left;
	delete p;
}
template <typename T>
void MaxHBLT<T>::h_show(TNode<T> *node) const
{
	if (node)
	{
		h_show(node->left);
		std::cout <<node->data <<" ";
		h_show(node->right);
	}
}