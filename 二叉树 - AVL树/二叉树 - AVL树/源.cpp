#include "avl_tree.h"

int main()
{
	AVL_TREE<int> tree;
	for (int i = 1; i <= 10; ++i)
		tree.insert(i);

	while (1);
	return 0;
}