/********************************************************************
    purpose:    �Թ�·��Ѱ��
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/20
	explain:
				ͨ��ջ����·�����߽���·ʱ������Ѱ������·��
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
	pos offset[4];	//������ƫ����
	offset[0].row = 0, offset[0].col = 1;	//��
	offset[1].row = 1, offset[1].col = 0;	//��
	offset[2].row = 0, offset[2].col = -1;	//��
	offset[3].row = -1, offset[3].col = 0;	//��
	int option = 0, lastoption = 3;	//ƫ�Ʒ���ѡ��
	pos here, tmp;	//��ǰλ�ã���ʱ����
	here.col = 1, here.row = 1;	//���
	int r, c;
	maze[1][1] = 1;	//���������ɶ���Ѱ�õ�
	while (here.col != m || here.row != m)	//��������
	{
		while (option <= lastoption)	//Ѱ�ҿ��з���
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)	//�ҵ����з���
				break;
			option++;	//��һ����
		}
		if (option <= lastoption)	//�ҵ��˿��з���
		{
			path.push(here);	//��һλ�ô��·��
			here.row = r;	//��ǰλ��ת��
			here.col = c;
			maze[r][c] = 1;	//��������ֹ�����һ�
			option = 0;	//�����´�Ѱ��
		}
		else
		{
			if (path.empty())	//��·����
				return false;
			tmp = path.top();
			path.pop();	//����
			if (tmp.row == here.row)	//��һλ���뵱ǰλ�ñȽ���ȷ��Ѱ�ҷ���
				option = 2;
			else
				option = 3;
			here = tmp;	//��ǰλ��ת��
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