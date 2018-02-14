//用于建立入边图从而统计每个论文的引用量、为排序功能服务
#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;
#define Vertices 16980       //定义论文总数

struct Edge 
{           //定义论文引用关系的边结构
	int dest;        //引用论文号
	Edge *link;
};
struct Vertex
{
	Edge *adj;
	int source;
	char *title;
	int num;        //每个论文的被引用数
};

class Graph 
{            //用邻接表形式存储关系图
public:
	Vertex *NodeTable;
	Graph(int sz = Vertices);
	~Graph();
	bool Insert(int v1, int v2);
private:
	int SZ;

};

Graph::Graph(int sz) {                 //构造函数
	SZ = sz;
	NodeTable = new Vertex[sz];
	for (int i = 0; i<sz; i++) {
		NodeTable[i].source = i + 1;
		NodeTable[i].num = 0;
		NodeTable[i].adj= NULL;
		NodeTable[i].title = NULL;
	}    //初始化
}

Graph::~Graph()//析构函数
{                         
	for (int i = 0; i<SZ; i++) 
	{
		Edge *p = NodeTable[i].adj;
		while (p != NULL) 
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

bool Graph::Insert(int a, int b)
{                 //ab边
	Edge *p = NodeTable[a - 1].adj;
	while (p != NULL&&p->dest != b)
		p = p->link;  //寻找邻接顶点v2
	if (p != NULL)
		return false;         //找到此边，不插入
	p = new Edge;
	p->dest = b;
	p->link = NodeTable[a - 1].adj;
	NodeTable[a - 1].adj = p;
	NodeTable[a - 1].num++;         //被引用次数+1
	return true;
}


void order(int *r, Graph &G) 
{                    
	for (int i = 0; r[i]>0 && i<20; i++)
	{
		int max = i;
		for (int j = i; r[j]>0; j++)
		{
			if (G.NodeTable[r[j] - 1].num>G.NodeTable[r[max] - 1].num)max =j;
		}
		cout << G.NodeTable[r[max] - 1].source << "   被引用数" << G.NodeTable[r[max] - 1].num << endl;
		r[max] = r[i];
	}

}
int main()
{

	ifstream fin2("e:\\link.txt");          //打开文件
	Graph whf;
	int x;	char c;
	int num = 0;
	int doc = 0;     //定义当前论文号和被引用数，   主要为了消除文件格式开头类似“ ##1:0：”的影响。
	while (!fin2.eof()) 
	{
		fin2 >> c >> c >> num >> c >> doc >> c;          // 消除格式影响。
		for (int i = 0; i < doc; i++)
		{
			fin2 >> x;                            //将x论文插入引用节点中。
			whf.Insert(num, x);
		}

	}
	cout << "succ" << endl;
	fin2.close();
	int f;
	cout << "number" << endl;
	while (1) {
		cin >> f; 
		if (f > 16980) 
		{
			cout << "error" << endl; continue; 
		}
		if (f == 0)break;
		cout << whf.NodeTable[f - 1].num << endl;
		if (whf.NodeTable[f - 1].num == 0)continue;
		for (Edge *t = whf.NodeTable[f - 1].adj; t != NULL; t = t->link)
			cout << ' ' << t->dest << ' ';
		cout << endl;
	}
}
/*ranks = new int *[count];    //存放每一个单词的记录表
C = new boolqueue[choosenum + 1];  //初始化布尔队列，C[n]负责存之前n-1个单词布尔检索的结果，B[n]负责存第n个新的单词布尔检索的结果，不断循环输出最终结果。
B = new boolqueue[choosenum];
ThisTable.boolSearch(str[0], C[0]);
for (int o = 0; o<choosenum; o++)
{
	ThisTable.boolSearch(str[o + 1], B[o]);
	if (choose[o] == 1)And(C[o], B[o], C[o + 1]);          //将C[O]和B[o]进行了布尔检索的结果存入C[o+1}以供下次循环使用。
	if (choose[o] == 2) or (C[o], B[o], C[o + 1]);
}
int *rank = new int[17000], i = 0, tag = 1;
if (C[choosenum].first->num == 0) { cout << "没有对应结果!" << endl;  continue; }  //若没有结果，则跳出此次查询
for (boolnode *p = C[choosenum].first; p != NULL; p = p->next, i++) {
	cout << p->num << endl;
	rank[i] = p->num;
}
cout << "按被引用数排序后,排名前20的是：" << endl;
Rank(rank, GG);*/