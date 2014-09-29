#include <iostream>
#include <fstream>

std::ifstream fin;
std::ofstream fout;
using namespace std;

const int D = 4096,
		alpha = 256,
		ByteSize = 8,
		HalfByte = 4,
		AllBit = 255,
		HalfBit = 15;
int used, state = 0;
char LastChar, LeftHalf;
unsigned long outch;
struct
{
	long int code;
}ht[D];
bool search(long int cd, int& tk)
{
	for (int i = 0; i < used; i++)
		if (ht[i].code == cd)
		{
			tk = i;
			return true;
		}
	return false;
}
bool openfile()
{
	fin.open("123.txt", std::ios_base::binary);
	fout.open("123.lzw", std::ios_base::binary | std::ios_base::out);
	if (fin.fail() || fout.fail())
		return false;
	else
		return true;
}
void output(long val)
{
	unsigned char ch, ck;
	if (state)
	{
		ch = (val >> ByteSize & HalfBit) | (LeftHalf << HalfByte);
		ck = val & AllBit;
		
		fout.put(ch);
		fout.put(ck);
		state = 0;
	}
	else
	{
		ch = val >> HalfByte;
		fout.put(ch);
	
		LeftHalf = val & HalfBit;
		state = 1;
	}
}
void compress()
{
	int i;
	for (i = 0; i < alpha; i++)	//用256个字符进行初始化
		ht[i].code = i;
	used = alpha; //已使用

	char ch;
	unsigned long cd, pcode;
	int tk;
	fin.get(ch);
	pcode = ch;
	while(!fin.eof())
	{
		fin.get(ch);
		
		cd = (pcode << ByteSize) + (unsigned char)ch;
		if (fin.eof())
		{
			//break;
		}
		if (search(cd, tk))
		{
			pcode = tk;
		}
		else
		{
			output(pcode);
			if (used < D)
			{
				ht[used].code = (pcode << ByteSize | ((unsigned)ch));
				used++;
			}
			pcode = ch;
		}
	}
	output(pcode);
	if (state)
	{
		cout <<"error\n";
		ch = LeftHalf << HalfByte;
		fout.put(ch);
	}
}
int main()
{

	if (openfile())
		cout <<"file ready!\n";
	compress();
	cout <<"ok\n";
	int i;
	/*
	for (i = 0; i < 256; i++)
		cout <<i <<"\t"<< ht[i].key <<"\t" <<char(ht[i].code) <<endl;
		*/
	for (i = 256; i < used; i++)
		//cout <<i  <<"\t" <<(ht[i].code>>8) <<"  "<<char(ht[(ht[i].code>>8)].code)<<"  "<<char(ht[i].code & AllBit) <<endl;
	fin.close();
	fout.close();
	return 0;
}
