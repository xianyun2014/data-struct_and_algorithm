#include "List.h"

void init(List<stu> &chain);	//初始化测试数据
int main()
{
	List<stu> chain;
	init(chain);
	chain.show();
	binsort(chain, 6);
	chain.show();
	return 0;
}
void init(List<stu> &chain)
{
	stu temp;
	for (int i = 1; i <= 50; ++i)
	{
		temp.set(rand()%7,"a");
		chain.push(temp);
	}
}