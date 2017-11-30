#include "stdafx.h"
#include"readname.h"
#include"command.h"

int main()
{
	while (1)
	{
		cout << "1.huffman compress" << endl;
		cout << "2.huffman decompress" << endl;
		cout << "3.exit" << endl;
		if(command()==1) continue; //执行command()，返回1，则输入指令错误
	}
	return 0;
}
