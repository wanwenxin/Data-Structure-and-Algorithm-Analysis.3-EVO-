#pragma once
#include"node.h"
#include<stdio.h> 
#include<cstdlib>
#include<fstream>
#include<iostream>
#include <math.h>
#define maxval 10000        //最大权值  
#define maxsize 1000        //数组大小的最大值  
#define maxlongth 1000 
using namespace std;



class Huffman
{
public:
	char temp[maxlongth];           //暂存读入字符串
	char text[maxlongth];      //存入读取文件的全部内容
	char binarycode[maxlongth];     //存放编码好的二进制串
	char decode_ch[maxlongth];      //存放翻译好的字符串
	char text_ch[M];        //标记读入huffman文件的字符
	int text_wight[M];      //统计读入huffman文件的字符对应权值
	char wight_in_text[N+3];   //写入text的字符权值,末尾是\r\n\0(写入)或\0（读入）

	int decimal[maxsize];
	char binary[maxsize];

	HuffmanTree tree[M];    //huffman树
	CodeType code[N];       //huffman编码表
public:
	//  Huffman();
	// ~Huffman();
	void initialize(char text[], char text_ch[], int text_wight[]);       //初始化temp_ch[N] temp_wight[N];统计huffman树文件的各字符权重
	void initialize_simpe(char text_ch[], int temp_wight[]);              //直接初始化
	void code_01(char temp[], char text[]);                               //6位01码编译成字符
	void decode_01(char temp[], char text[]);                             //字符解码成6位01码

	void infile_read(char temp[], char text[]);                           //从源文件中读取数据,存入temp[]
	void find_sort(char temp[], char text[]);                             //将读入的temp存入text结尾void binary_to_H95(char huffman_95[], char text[]);             //现将二进制转为95进制，再存储

	void CreateHuffmanTree(HuffmanTree tree[], char text_ch[], int text_wight[]);     //创建Huffman树  
	void write_tree_weight(int text_wight[], char wight_in_text[]);    //保存入text的权值
	void read_tree_weight(int text_wight[], char wight_in_text[]);     //读取自text的权值
	void HuffmanCode(CodeType code[], HuffmanTree tree[]);          //根据Huffman树求出Huffman编码存储在code数组中  
	void incode(CodeType code[], char temp[], char binarycode[]);   //将字符串temp编码，变成“01”串保存在数组binarycode中  
	void decode(HuffmanTree tree[], char temp[], char decode_ch[]); //将“01”字符串str进行译码，直接输出  
};

void Huffman::find_sort(char temp[], char text[])
{
	int flag = 0;
	int cur_temp = 0, cur_text = 0;
	for (int i = 0;i < maxlongth;i++)
	{
		cur_text = i;
		if (text[cur_text] == '\0')   //找到目标
		{
			if(cur_text!=0)  //不是首句
			{
				text[cur_text] = '\r';
				cur_text++;
				text[cur_text] = '\n';
				cur_text++;
			}
			flag = 1;
			while(temp[cur_temp] != '\0')  //循环导入
			{
				text[cur_text] = temp[cur_temp];
				cur_temp++, cur_text++;
			}
			text[cur_text] = '\0';     //句尾加上终止标志
		}
		if (flag == 1) break;   //完成读入，跳出循环
	}

}


void Huffman::infile_read(char temp[], char text[])   //读取源文件到缓冲区
{
	text[0] ='\0';
	infile.seekg(0, ios::beg);
	while (!infile.eof())
	{
		infile.getline(temp, 1000, '\n');   //读入当前行内容
		find_sort(temp, text);
	}
}

void Huffman::initialize(char text[], char text_ch[], int text_wight[])  //将huffman树M个结点初始化,weight全部置0
{
	for (int i = 0; i < N-2;i++)   //读入所有可显示字符
	{
		text_ch[i] = i + ' ';
		text_wight[i] = 0;
	}
	text_ch[N - 2] = '\r';
	text_wight[N - 2] = 0;
	text_ch[N - 1] = '\n';
	text_wight[N - 1] = 0;       //最后读入组合换行符
	for (int i = N; i < M;i++)  //后续节点位置空符
	{
		text_ch[i] = '\0';
		text_wight[i] = 0;
	}
	for (int i = 0; text[i] != '\0';i++)
	{
		if (text[i] == '\r')
		{
			text_wight[N - 2]++;//‘\r’权重加一
		}
		else if (text[i] == '\n')
		{
			text_wight[N - 1]++;//‘\n’权重加一
		}
		else //text[i]为95个可显示字符
		{
			int p = text[i] - ' ';
			text_wight[p]++;          //对应权值加1
		}
	}
}


void Huffman::initialize_simpe(char text_ch[], int text_wight[])  //直接将huffman树M个结点字符初始化,weight全部置0
{
	for (int i = 0; i < N - 2;i++)   //读入所有可显示字符
	{
		text_ch[i] = i + ' ';
	}
	text_ch[N - 2] = '\r';
	text_ch[N - 1] = '\n';      //最后读入组合换行符
	for (int i = N; i < M;i++)  //后续节点位置空符
	{
		text_ch[i] = '\0';
		text_wight[i] = 0;
	}
}

void Huffman::code_01(char binarycode[], char temp[])
{
	int flag = strlen(binarycode)%6;  //01码总数除6的余
	int cur_binary = flag;
	int cur_temp = flag + 1;
	int sum = 0;
	for (int i = 0;i < flag;i++)
	{
		temp[i] = binarycode[i];
	}
	temp[flag] = (' ' + 67);       //不属于从空格开始的64位符号
	while (cur_binary < strlen(binarycode))
	{
		for (int i = 6;i > 0;i--)
		{
			if (binarycode[cur_binary]== '1')
			{
				sum += (int)pow(2, i - 1);
			}
			cur_binary++;
		}
		temp[cur_temp] = (sum + ' ');
		cur_temp++;
		sum = 0;
	}
	temp[cur_temp] = '\0';
}

void Huffman::decode_01(char temp[], char text[])
{
	int cur_temp = 1;     //比text多1，以过滤RIP
	int cur_text = 0;
	int num = 0;
	for (int i = 0;temp[i] != (' ' + 67);i++)
	{
		text[i] = temp[i];
		cur_temp++;
		cur_text++;
	}
	while (temp[cur_temp] != '\0')
	{
		num = (temp[cur_temp] - ' ');
		for (int i = 6;i > 0;i--)
		{
			if(num/ (int)pow(2, i - 1)==1)
			{
				num -= (int)pow(2, i - 1);
				text[cur_text] = '1';
			}
			else
			{
				text[cur_text] = '0';
			}
			cur_text++;
		}
		cur_temp++;
	}
	text[cur_text] = '\0';
}

void Huffman::write_tree_weight(int text_wight[], char wight_in_text[])
{
	for (int i = 0;i < N;i++)
	{
		wight_in_text[i] = text_wight[i]+33;
		//cout << i <<"  "<< text_wight[i] <<"  " << wight_in_text[i] << endl;    //重要检测
	}
	wight_in_text[N] = '\r';
	wight_in_text[N+1] = '\n';
	wight_in_text[N+2] = '\0';
}

void Huffman::read_tree_weight(int text_wight[], char wight_in_text[])
{
	infile.getline(wight_in_text, 1000, '\n');
	for (int i = 0;i < N ;i++)
	{
		text_wight[i] = wight_in_text[i]-33;
		//cout << i << "  " << text_wight[i] << "  " << wight_in_text[i] << endl;    //重要检测
	}
}

void Huffman::CreateHuffmanTree(HuffmanTree tree[], char text_ch[], int text_wight[])
{
	int i, j;
	int p1, p2;          //p1,p2记录最小权值及次小权值节点在数组中的下标  
	int min1, min2;      //min1记录最小权值，min2记录次小权值  

	for (i = 0;i<M;i++)        //初始化Huffman树的M个节点  
	{
		tree[i].Lchild = -1;
		tree[i].Rchild = -1;
		tree[i].parent = -1;
	}

	//输入Huffman树前N个节点的信息，即待编码的字符及其权值  
	for (i = 0;i<M;i++)
	{
		tree[i].ch = text_ch[i];
		tree[i].weight = text_wight[i];
	}

	//进行N-1次合并，生成N-1个新节点  
	//每次找到权值最小的两个单个节点（即无父节点的节点）+，合并形成新节点，更改这两个节点的父节点信息、新节点的权值及左右孩子节点信息  
	for (i = N;i<M;i++)
	{
		p1 = p2 = 0;          //最小权值节点及次小权值节点对应下标初始化为0  
		min1 = min2 = maxval; //最小权值及次小权值初始化为权值最大值  
		for (j = 0;j<i;j++)   //依次检测Huffman树的前i个节点  
		{
			if (tree[j].parent == -1)     //若该节点无父节点  
			{
				if (tree[j].weight<min1)  //若该节点的权值小于最小权值，  
				{                         //将最小权值赋给次小权值，该节点的权值赋给最小权值作为最小权值  
					min2 = min1;          //并更改对应p1,p2的值,使之指向对应节点的下标  
					min1 = tree[j].weight;
					p2 = p1;
					p1 = j;
				}
				else
				{
					if (tree[j].weight<min2) //若该节点的权值大于最小权值，小于次小权值，  
					{                        //将该节点的权值赋给次小权值，该节点的下标赋给p2  
						min2 = tree[j].weight;
						p2 = j;
					}
				}
			}
		}

		tree[p1].parent = i; //更改权值最小两个节点的父节点信息  
		tree[p2].parent = i;
		tree[i].Lchild = p1; //更改父节点左右孩子信息及权值  
		tree[i].Rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}

void Huffman::HuffmanCode(CodeType code[], HuffmanTree tree[]) //根据Huffman树求出Huffman编码存储在code数组中  
{
	int i, c, p;
	CodeType cd;//缓冲变量  
	for (i = 0;i<N;i++)//依次检测前N个节点，前N个节点为叶子节点，即从Huffman从下往上获得单个字符的编码  
	{
		cd.start = N;
		cd.ch = tree[i].ch;
		c = i;              //c为当前节点  
		p = tree[i].parent; //p为当前  
		while (p != -1)
		{
			cd.start--;
			if (tree[p].Lchild == c)
				cd.bits[cd.start] = '0';//tree[i]是左子树，生成代码'0'  
			else
				cd.bits[cd.start] = '1';//tree[i]是右子树，生成代码'1'  
			c = p;
			p = tree[p].parent;
		}
		code[i] = cd;//第i+1个字符的编码存入code[i]  
	}
}

void Huffman::incode(CodeType code[], char text[], char binarycode[])//编码  
{
	int i, k = 0;
	for (i = 0;text[i] != '\0';i++)
	{
		int j = 0, p = 0;
		while (code[j].ch != text[i])
			j++;
		for (p = code[j].start;p < N;p++)
			binarycode[k++] = code[j].bits[p];
	}
	binarycode[k] = '\0';//注意！  
}

void Huffman::decode(HuffmanTree tree[], char text[], char decode_ch[])//译码  
{
	int cur = 0;
	int j = 0, i = M - 1;//tree[M-1]为根节点，从根节点开始译码  
	while (text[j] != '\0')
	{
		if (text[j] == '0')
			i = tree[i].Lchild;//走向左孩子  
		else if (text[j] == '1')
			i = tree[i].Rchild;//走向右孩子  
		if (tree[i].Rchild == -1)//tree[i]是叶子节点  
		{
			decode_ch[cur]=tree[i].ch;
			cur++;
			i = M - 1;//回到根节点 
		}
		j++;
	}
	if (tree[i].Lchild != -1 && text[j] != '\0')//字符串读完，但未到叶子节点，则输入01码有错  	
	{
		printf("ERROR!");
	}
	decode_ch[cur] = '\0';
}
