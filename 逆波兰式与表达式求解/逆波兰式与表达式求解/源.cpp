/***************
�沨��ʽ����׺��ʾ��
  Ԥ���� �������� ������ʽ->������ʽ(infix to postfix)
	  �㷨��
	  while(���ʽ�ǿ�)
		if (����������)
		  ֱ�����
		else if (����������op)
		  op��( ֱ����ջs
		  op��) s.push�����ֱ��(
		  op���������㣬��
			if (sΪ�� || s.topΪ( || op ���ȼ����� s.top)
			  op ��ջ
			else
			  s.push���
	  if (!s.empty)
		s.push���
  ����
	  �㷨:
	  if (����������)
	      ��ջs
	  else (����������)
	      s.push����Ԫ�ؽ������㣬�����ջ
*******************/
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
typedef struct tagCalc
{
	char op;	
}Calc;
stack<Calc> s;
Calc calc;
void fun(char *str, char *source)
{
	char *p = source, *a = str;
	float f;
	int pa, pb;
	while (*p != '\0')
	{
		if (isspace(*p))
		{
			++p;
			continue;
		}
		if (NULL != strchr("0123456789.", *p))
		{
			sscanf(p, "%f", &f);
			printf("%f", f);
			sprintf(a, "%f", f);
			while (*p != '\0' && NULL != strchr("0123456789.", *p))
				++p;
		}
		else if (NULL != strchr("*-/+()", *p))
		{
			if ('(' == *p)
			{
				calc.op = *p;
				s.push(calc);
			}
			else if (')' == *p)
			{
				while (!s.empty())
				{
					calc = s.top();
					s.pop();
					if ('(' == calc.op)
						break;
					sprintf(a++, "%c", calc.op);
					printf("%c", calc.op);
				}
			}
			if (s.empty() || s.top().op == '(' || (NULL != strchr("*/", *p) && NULL != strchr("+-", s.top().op)))
			{
				calc.op = *p;
				s.push(calc);
			}
			else
			{
				calc = s.top();
				s.pop();
				sprintf(a++, "%c", calc.op);
				printf("%c", calc.op);
			}
			++p;
		}
		else
			++p;
	}
	while (!s.empty())
	{
		calc = s.top();
		s.pop();
		sprintf(a++, "%c", calc.op);
		printf("%c", calc.op);
	}
}
int main()
{
	char arr[2000], str[2000];
	char ch, *p = str;
	while ((ch = getchar()) && ch != '\n')
	{
		if (NULL != strchr("0123456789.*-/+()", ch))
			*p++ = ch;
	}
	*p = '\0';
	printf("str:%s\n", str);
	
	fun(arr, str);
	while (1);
	return 0;
}
