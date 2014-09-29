/********************************************************************
    purpose:    �Թ����·��Ѱ��
    author:     xianyun1230
    QQ:         836663997
    e-mail:     xianyun1230@163.com
    created:    2014/02/20
	explain:
				ͨ�����а�����Բ�η��䲢��¼·������Ѱ�ҳ���
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

	pos offset[4];	//������ƫ����
	offset[0].row = 0, offset[0].col = 1;	//��
	offset[1].row = 1, offset[1].col = 0;	//��
	offset[2].row = 0, offset[2].col = -1;	//��
	offset[3].row = -1, offset[3].col = 0;	//��
	pos nbr; 
	int NumOfNbr = 4;	//�ĸ�Ѱ�ҷ���
	pos front;	//֮ǰλ��
	front.row = start.row;
	front.col = start.col;
	maze[front.row][front.col] = 2;
	do
	{
		for (int i = 0; i < NumOfNbr; ++i)	//Ѱ���ھ�
		{
			nbr.row = front.row + offset[i].row;
			nbr.col = front.col + offset[i].col;
			if (maze[nbr.row][nbr.col] == 0)
			{
				maze[nbr.row][nbr.col] = maze[front.row][front.col] + 1;	//·�����ȼ�1
				que.push(nbr);	//�������
			}
			if (nbr.row == end.row && nbr.col == end.col)	//Ѱ������
				break;
		}
		if (nbr.row == end.row && nbr.col == end.col)	
			break;
		else	//Ѱ����һ���ж�����λ��
		{
			if (que.empty()) //�޷��ҵ�����
				return false;
			front = que.front();	//���������,front���Խ���Բ�����ⲻ����ɢ
			que.pop();
		}
	}while(true);
	front.row = end.row;
	front.col = end.col;	
	while (front.row != start.row && front.col != start.col) //�ӳ��������Ѽ�·��
	{
		for (int i = 0; i < NumOfNbr; ++i)	//�����ĸ������·������
		{
			if (maze[front.row + offset[i].row][front.col + offset[i].col] == 
				maze[front.row][front.col] - 1)	//·�����ȼ�С
			{
				path.push(front);
				front.col += offset[i].col;	//λ���ƶ���Ϊ�´��Ѽ���׼��
				front.row += offset[i].row;
			}
		}
	}
	path.push(start);	//����ڼ���·��
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