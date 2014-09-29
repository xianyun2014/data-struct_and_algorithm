/********************************************************************
    purpose:    迷宫最短路径寻找
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/20
	explain:
				通过队列按近似圆形辐射并记录路径长度寻找出口
*********************************************************************/


#include <iostream>
#include <iomanip>
#include <queue>

const int m = 10;
short maze[m+2][m+2] = {
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,0,0,0,0,1,
	1,0,0,0,0,0,1,0,1,0,0,1,
	1,0,0,0,1,0,1,0,0,0,0,1,
	1,0,1,0,1,0,1,0,1,1,0,1,
	1,0,1,0,1,0,1,0,1,0,0,1,
	1,0,1,1,1,0,1,0,1,0,1,1,
	1,0,1,0,0,0,1,0,1,0,1,1,
	1,0,1,0,1,1,1,0,1,0,0,1,
	1,1,0,0,0,0,0,0,1,0,0,1,
	1,0,0,0,0,1,1,1,1,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
typedef struct
{
	short row, col;
}pos;

std::queue<pos> que, path;
bool findpath()
{
	pos start, end;
	start.row = start.col = 1;
	end.row = end.col = m;

	pos offset[4];	//各方向偏移量
	offset[0].row = 0, offset[0].col = 1;	//右
	offset[1].row = 1, offset[1].col = 0;	//下
	offset[2].row = 0, offset[2].col = -1;	//左
	offset[3].row = -1, offset[3].col = 0;	//上
	pos nbr; 
	int NumOfNbr = 4;	//四个寻找方向
	pos front;	//之前位置
	front.row = start.row;
	front.col = start.col;
	maze[front.row][front.col] = 2;
	do
	{
		for (int i = 0; i < NumOfNbr; ++i)	//寻找邻居
		{
			nbr.row = front.row + offset[i].row;
			nbr.col = front.col + offset[i].col;
			if (maze[nbr.row][nbr.col] == 0)
			{
				maze[nbr.row][nbr.col] = maze[front.row][front.col] + 1;	//路径长度加1
				que.push(nbr);	//进入队列
			}
			if (nbr.row == end.row && nbr.col == end.col)	//寻到出口
				break;
		}
		if (nbr.row == end.row && nbr.col == end.col)	
			break;
		else	//寻找下一个判定所在位置
		{
			if (que.empty()) //无法找到出口
				return false;
			front = que.front();	//因队列性质,front会以近乎圆形向外不断扩散
			que.pop();
		}
	}while(true);
	front.row = end.row;
	front.col = end.col;	
	while (front.row != start.row && front.col != start.col) //从出口往回搜集路径
	{
		for (int i = 0; i < NumOfNbr; ++i)	//遍历四个方向的路径长度
		{
			if (maze[front.row + offset[i].row][front.col + offset[i].col] == 
				maze[front.row][front.col] - 1)	//路径长度减小
			{
				path.push(front);
				front.col += offset[i].col;	//位置移动，为下次搜集做准备
				front.row += offset[i].row;
			}
		}
	}
	path.push(start);	//把入口加入路径
	return true;
}
int main()
{
	using namespace std;
	int j, k;
	for (j = 0; j < m+2; ++j)
	{
		for (k = 0; k < m+2; ++k)
			cout << setw(3)<<maze[j][k];
		cout <<endl;
	}
	cout <<endl;

	if (findpath())
		std::cout <<"ok\n";
	else
		std::cout <<"no\n";
	for (j = 0; j < m+2; ++j)
	{
		for (k = 0; k < m+2; ++k)
			cout <<setw(3) <<maze[j][k];
		cout <<endl;
	}
	cout <<endl;
	pos tmp;
	while (!path.empty())
	{
		tmp = path.front();
		path.pop();
		std::cout <<tmp.row <<"   " <<tmp.col <<std::endl;
	}
	cin.get();
	cin.get();
	return 0;
}