#define N 97                //叶子总数,即需编码字符的个数(95个可显示字符+2个‘\r’‘\n’)  
#define M 2*N-1             //节点总数  

typedef struct HuffmanTree//用于存储Huffman树中的节点信息  
{
	char ch;         //字符  
	int weight;      //权值  
	int Lchild;      //左孩子  
	int Rchild;      //右孩子  
	int parent;      //父节点  
}HuffmanTree;


typedef struct CodeType//用于存储单个字符的编码结果  
{
	char ch;        //字符  
	char bits[N];   //位串  
	int start;      //编码在位串中的起始位置  
}CodeType;
