/***************
逆波兰式即后缀表示法
  预处理 ———— 中序表达式->逆序表达式(infix to postfix)
	  算法：
	  while(表达式非空)
		if (遇到操作数)
		  直接输出
		else if (遇到操作符op)
		  op是( 直接入栈s
		  op是) s.push输出，直到(
		  op是四则运算，则
			if (s为空 || s.top为( || op 优先级高于 s.top)
			  op 入栈
			else
			  s.push输出
	  if (!s.empty)
		s.push输出
  计算
	  算法:
	  if (遇到操作数)
	      入栈s
	  else (遇到操作符)
	      s.push两个元素进行运算，结果入栈
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
