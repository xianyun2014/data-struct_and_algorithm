
#include "binarytree.h"

int main()
{
	binarytree<int> tree(12);
	for (int i = 0; i < 20; i++)
		tree.insert(rand()%300);
	tree.inorder();
	std::cout <<std::endl;
	tree.levelorder();
	std::cout <<std::endl <<tree.high() <<std::endl << tree.number() <<std::endl;
	return 0;
}