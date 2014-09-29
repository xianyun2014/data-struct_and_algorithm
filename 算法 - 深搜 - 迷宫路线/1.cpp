/********************************************************************
    purpose:    迷宫路线寻找
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/20
	explain:
				通过栈保存路径，走进死路时，回溯寻找其它路径
*********************************************************************/


#include <iostream>
#include <iomanip>
#include <stack>

const int m = 10;
bool maze[m+2][m+2] = {
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

std::stack<pos> path;

bool findpath()
{
	pos offset[4];	//各方向偏移量
	offset[0].row = 0, offset[0].col = 1;	//右
	offset[1].row = 1, offset[1].col = 0;	//下
	offset[2].row = 0, offset[2].col = -1;	//左
	offset[3].row = -1, offset[3].col = 0;	//上
	int option = 0, lastoption = 3;	//偏移方向选项
	pos here, tmp;	//当前位置，临时变量
	here.col = 1, here.row = 1;	//起点
	int r, c;
	maze[1][1] = 1;	//堵死，不可二次寻该点
	while (here.col != m || here.row != m)	//不到出口
	{
		while (option <= lastoption)	//寻找可行方向
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)	//找到可行方向
				break;
			option++;	//下一方向
		}
		if (option <= lastoption)	//找到了可行方向
		{
			path.push(here);	//上一位置存进路径
			here.row = r;	//当前位置转移
			here.col = c;
			maze[r][c] = 1;	//堵死，防止二次找回
			option = 0;	//用于下次寻找
		}
		else
		{
			if (path.empty())	//无路可找
				return false;
			tmp = path.top();
			path.pop();	//回溯
			if (tmp.row == here.row)	//上一位置与当前位置比较以确定寻找方向
				option = 2;
			else
				option = 3;
			here = tmp;	//当前位置转移
		}
	}
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
		cout <<"ok\n";
	else
		cout <<"no\n";
	pos tmp;
	while (!path.empty())
	{
		tmp = path.top();
		path.pop();
		cout <<tmp.row <<"   " <<tmp.col <<endl;
	}
	cin.get();
	cin.get();
	return 0;
}