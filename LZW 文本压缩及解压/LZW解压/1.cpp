#include <iostream>
#include <fstream>
#include "hashlist.h"

std::ifstream fin;
std::ofstream fout;

const int D = 4096,
		alpha = 256,
		ByteSize = 8,
		HalfByte = 4,
		AllBit = 255,
		HalfBit = 15;
int used, state = 0;
char LastChar, LeftHalf;
unsigned long outch;
char s[D];
int slen;
struct
{
	int pre;
	char ch;
}ht[D];

bool openfile()
{
	fin.open("123.lzw", std::ios_base::binary);
	fout.open("123-lzw.txt", std::ios_base::binary | std::ios_base::out);
	if (fin.fail() || fout.fail())
		return false;
	else
		return true;
}
bool getcode(int &code)
{
	char tch, tck;
	unsigned char ch, ck;
	fin.get(tch);
	ch = tch;
	if (fin.eof())
		return false;
	code = ch;
	if (state)
	{
		code = (LeftHalf << ByteSize) | ch;
		state = 0;
	}
	else
	{
		fin.get(tck);
		//if (fin.eof())
		//	return false;
		ck = tck;
		code = (code << HalfByte) | (ck >> HalfByte);
		LeftHalf = ck & HalfBit;
		state = 1;
	}
	return true;
}
void output(int code)
{
	slen = -1;
	while (code >= alpha)
	{
		s[++slen] = ht[code].ch;
		code = ht[code].pre;
	}
	s[++slen] = code;
	for (int i = slen; i >= 0; --i)
		fout.put(s[i]);
}
void decompress()
{
	int i, pcode, ccode;
	for (i = 0; i < alpha; i++)	//用256个字符进行初始化
		ht[i].ch = i;
	used = alpha; //已使用

	if (getcode(pcode))
	{
		s[0] = pcode;
		fout.put(s[0]);
		slen = 0;

		while (getcode(ccode))
		{
			if (ccode < used)
			{
				output(ccode);
				if (ccode < D)
				{
					ht[used].pre = pcode;
					ht[used].ch = s[slen];
					used++;
				}
			}
			else
			{
				ht[used].pre = pcode;
				ht[used].ch = s[slen];
				used++;
				output(ccode);
			}
			pcode = ccode;
		}
	}
}
int main()
{
	using namespace std;
	if (openfile())
		cout <<"file ready!\n";
	decompress();
	cout <<"ok\n";
	for (int i = 0; i < used; i++)
		cout <<i <<"\t"<< ht[i].pre <<" "<<ht[ht[i].pre].ch<<" " <<ht[i].ch <<endl;
	fin.close();
	fout.close();
	return 0;
}
