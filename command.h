#include <stdlib.h>
#include <iostream>
#include"readname.h"
#include"Huffman.h"
int command()
{
	int command = 0;
	cin >> command;
	if (command == 1) //编码
	{
		readname(); //打开文件

		Huffman HF;
		HF.infile_read(HF.temp, HF.text);                           //读入huffman文件存入temp[]
		HF.initialize(HF.text, HF.text_ch, HF.text_wight);          //初始化
		HF.CreateHuffmanTree(HF.tree, HF.text_ch, HF.text_wight);   //创建huffman树tree[]
		HF.write_tree_weight(HF.text_wight, HF.wight_in_text);      //int权值变为char权值
		cout << HF.wight_in_text;
		outfile.write(HF.wight_in_text, N+2);  //char权值写入并换行
		HF.HuffmanCode(HF.code, HF.tree);           //由huffman树tree[]得编码code[]
		HF.incode(HF.code, HF.text, HF.binarycode); //根据翻译表code[]，将待编码得temp[]编译成二进制存入binarycode[]
		outfile.write(HF.binarycode, strlen(HF.binarycode));   //将binarycode[]输出到outoutfile

		close_file(); //关闭文件
	}
	else if (command == 2) //译码
	{
		readname(); //打开文件

		Huffman HF;
		HF.read_tree_weight(HF.text_wight, HF.wight_in_text);       //从文件读入char权值，并变为int权值;
		//cout << "1" << endl;
		HF.initialize_simpe(HF.text_ch, HF.text_wight);             //直接初始化
		//cout << "2" << endl;
		HF.CreateHuffmanTree(HF.tree, HF.text_ch, HF.text_wight);   //创建huffman树tree[]
		//cout << "3" << endl;
		infile.getline(HF.text, 1000, '\n');                  //读入源文件文件（待翻译得01串）存入temp[]
		//cout << HF.text << endl;
		//cout << "4" << endl;
		HF.decode(HF.tree, HF.text, HF.decode_ch);  //根据huffman树，将待翻译的temp[]翻译成字符串存入decode_ch[]
		//cout << "5" << endl;
		outfile.write(HF.decode_ch, strlen(HF.decode_ch));   //将decode_ch[]输出到outoutfile

		close_file(); //关闭文件
	}
	else if (command == 3) //退出
	{
		exit(0);
	}
	else //输入错误指令
	{
		cout << "error command,please re-enter";
		return 1;
	}
	return 0;
}
