//���ڽ������ͼ�Ӷ�ͳ��ÿ�����ĵ���������Ϊ�����ܷ���
#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;
#define Vertices 16980       //������������

struct Edge 
{           //�����������ù�ϵ�ı߽ṹ
	int dest;        //�������ĺ�
	Edge *link;
};
struct Vertex
{
	Edge *adj;
	int source;
	char *title;
	int num;        //ÿ�����ĵı�������
};

class Graph 
{            //���ڽӱ���ʽ�洢��ϵͼ
public:
	Vertex *NodeTable;
	Graph(int sz = Vertices);
	~Graph();
	bool Insert(int v1, int v2);
private:
	int SZ;

};

Graph::Graph(int sz) {                 //���캯��
	SZ = sz;
	NodeTable = new Vertex[sz];
	for (int i = 0; i<sz; i++) {
		NodeTable[i].source = i + 1;
		NodeTable[i].num = 0;
		NodeTable[i].adj= NULL;
		NodeTable[i].title = NULL;
	}    //��ʼ��
}

Graph::~Graph()//��������
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
{                 //ab��
	Edge *p = NodeTable[a - 1].adj;
	while (p != NULL&&p->dest != b)
		p = p->link;  //Ѱ���ڽӶ���v2
	if (p != NULL)
		return false;         //�ҵ��˱ߣ�������
	p = new Edge;
	p->dest = b;
	p->link = NodeTable[a - 1].adj;
	NodeTable[a - 1].adj = p;
	NodeTable[a - 1].num++;         //�����ô���+1
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
		cout << G.NodeTable[r[max] - 1].source << "   ��������" << G.NodeTable[r[max] - 1].num << endl;
		r[max] = r[i];
	}

}
int main()
{

	ifstream fin2("e:\\link.txt");          //���ļ�
	Graph whf;
	int x;	char c;
	int num = 0;
	int doc = 0;     //���嵱ǰ���ĺźͱ���������   ��ҪΪ�������ļ���ʽ��ͷ���ơ� ##1:0������Ӱ�졣
	while (!fin2.eof()) 
	{
		fin2 >> c >> c >> num >> c >> doc >> c;          // ������ʽӰ�졣
		for (int i = 0; i < doc; i++)
		{
			fin2 >> x;                            //��x���Ĳ������ýڵ��С�
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
/*ranks = new int *[count];    //���ÿһ�����ʵļ�¼��
C = new boolqueue[choosenum + 1];  //��ʼ���������У�C[n]�����֮ǰn-1�����ʲ��������Ľ����B[n]������n���µĵ��ʲ��������Ľ��������ѭ��������ս����
B = new boolqueue[choosenum];
ThisTable.boolSearch(str[0], C[0]);
for (int o = 0; o<choosenum; o++)
{
	ThisTable.boolSearch(str[o + 1], B[o]);
	if (choose[o] == 1)And(C[o], B[o], C[o + 1]);          //��C[O]��B[o]�����˲��������Ľ������C[o+1}�Թ��´�ѭ��ʹ�á�
	if (choose[o] == 2) or (C[o], B[o], C[o + 1]);
}
int *rank = new int[17000], i = 0, tag = 1;
if (C[choosenum].first->num == 0) { cout << "û�ж�Ӧ���!" << endl;  continue; }  //��û�н�����������˴β�ѯ
for (boolnode *p = C[choosenum].first; p != NULL; p = p->next, i++) {
	cout << p->num << endl;
	rank[i] = p->num;
}
cout << "���������������,����ǰ20���ǣ�" << endl;
Rank(rank, GG);*/