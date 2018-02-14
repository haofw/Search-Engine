#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;
#define Vertices 16980       //定义论文总数



//////////////////////////////////////////图的类定义///////////////////////////////////////
struct Edge				//边
{           
	int dest;        //论文号
	Edge *link;
};
struct Vertex
{
	Edge *adj;
	int data;
	char *title;
	int num;        //入度（引用次数）
};
class Graph			//邻接表
{            
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
		NodeTable[i].data = i + 1;
		NodeTable[i].num = 0;
		NodeTable[i].adj = NULL;
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
bool Graph::Insert(int a, int b)//插入边ab
{              
	Edge *p = NodeTable[a - 1].adj;
	while (p != NULL&&p->dest != b) //寻找邻接顶点b
		p = p->link; 
	if (p != NULL)
		return false;         //找到此边，不插入
	p = new Edge;
	p->dest = b;
	p->link = NodeTable[a - 1].adj;
	NodeTable[a - 1].adj = p;
	NodeTable[a - 1].num++;         //入度（引用次数）+1
	return true;
}
void order(int *r, Graph &G)		//对一个数组中的值排序输出
{
	for (int i = 0; i<20000 && r[i]>0; i++)
	{
		int max = i;
		for (int j = i; r[j]>0; j++)//循环寻找引用次数最大的并输出此顶点值和入度，找到后把r[i]赋值给r[max],进行下一波循环找第二大的输出
		{
			if (G.NodeTable[r[j] - 1].num>G.NodeTable[r[max] - 1].num)
				max = j;
		}
		cout << G.NodeTable[r[max] - 1].data<<"  入度" << G.NodeTable[r[max] - 1].num << endl;
		r[max] = r[i];
	}

}




/////////////////////////////////////////链表的类定义////////////////////////////////////////
struct Node			//链表节点
{
	int Data;
	Node*next;
	Node(int Data) : Data(Data), next(NULL) {};
};
class list			//链表类
{
public:
	Node*head;
public:
	list()
	{
		head = NULL;
		head = new Node(NULL);
	}
	void insertlist(int num);
	//void deletelist(int aData);
	void outputlist();
	int* creat();
	int deleteduplicate();
	Node*gethead() { return head; }
};
int list::deleteduplicate()			//删除重复链表
{
	if (head == NULL)
		return -1;
	Node *p, *q, *r;
	p = head;
	while (p)    // p用于遍历链表
	{
		q = p;
		while (q->next) // q遍历p后面的结点，并与p数值比较
		{
			if (q->next->Data == p->Data)
			{
				r = q->next; // r保存需要删掉的结点
				q->next = r->next;   // 需要删掉的结点的前后结点相接
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return 0;
}
void list::insertlist(int num)  //头插法插入
{
	Node *p;

	p = new Node(num);
	if(head->next==NULL)
	{
		p->next = head->next;
		head->next = p;
	}
	else if (head->next->Data != p->Data)
	{
		p->next = head->next;
		head->next = p;
	}
	
}
void list::outputlist()			//输出表中元素
{
	Node*current = head->next;
	while (current != NULL)
	{
		cout << current->Data << " ";
		current = current->next;
	}
	cout << endl;
}




/////////////////////////////////////////二叉搜索树的定义及函数////////////////////////////////////////
typedef struct node				//二叉搜索树节点   包括节点的值，左右孩子，链表
{
	string value;
	struct node *left;
	struct node *right;
	list A;
	node(string value) : value(value), left(NULL), right(NULL) {};
}NODE, *BST;
void insert(BST &p, string value, int num)		//递归插入树节点
{
	if (p == NULL)
	{
		p = new NODE(value);
		p->A.insertlist(num);

	}
	else
	{
		if (value < p->value)
			insert(p->left, value, num);

		else if (value > p->value)
			insert(p->right, value, num);
		else
		{
			p->A.insertlist(num);
			//cout << "duplicate" << endl;
		}
	}
}
/*void inOrder(BST p)			
{
	if (p != NULL)
	{
		inOrder(p->left);
		cout << p->value << "->";
		p->A.deleteduplicate();
		p->A.outputlist();
		inOrder(p->right);
	}
}*/
void clear(BST &root)
{
	if (root != NULL)
	{
		clear(root->left);
		clear(root->right);

		delete root;
		root = NULL;
	}
}
void find1(BST &p, string value)		//倒排索引时用递归找到节点并输出节点的链表
{
	if (p == NULL)
		cout << "error" << endl;
	else if (value < p->value)
		find1(p->left, value);
	else if (value > p->value)
		find1(p->right, value);
	else
	{
		p->A.deleteduplicate();
		p->A.outputlist();
	}

}
Node *find(BST &p, string value)			//实现与或时用到的函数，返回二叉树节点的链表的头
{
	while (value != p->value)
	{
		if (value < p->value)
			p = p->left;
		else if (value > p->value)
			p = p->right;
	}
	p->A.deleteduplicate();
	return p->A.head;
	
}




////////////////////////////////////////与或的实现/////////////////////////////////////////////////////
int* list::creat()				//返回一个数组便于进行根据入度排序输出
{
	int *r = new  int[17000];
	int i = 0;
	Node*current = head->next;
	while (current != NULL)
	{
		r[i] = current->Data;
		current = current->next;
		i = i + 1;
	}
	return r;
}
void myor (BST &p, Graph &whf,string a, string b)    //对a,b两个节点的链表进行或操作，结果加到一个新的链表mylist中
{    
	BST q1 = p;
	BST q2 = p;
	Node *head1 = find(q1, a)->next;
	Node *head2 = find(q2, b)->next;
	list myor;
	while (head1 != NULL || head2 != NULL)
	{
		if (head1 == NULL) {
			while (head2 != NULL) 
			{
				myor.insertlist(head2->Data);
				head2 = head2->next; 
			}
			break;
		}
		if (head2 == NULL) {
			while (head1 != NULL)
			{
				myor.insertlist(head1->Data);
				head1 = head1->next;
			}
			break;
		}
		if (head1->Data>head2->Data)
		{
			myor.insertlist(head1->Data);
			head1 = head1->next;
		}
		else if (head2->Data>head1->Data)
		{
			myor.insertlist(head2->Data);
			head2 = head2->next;
		}
		else 
		{
			myor.insertlist(head1->Data);
			head1 = head1->next;
			head2 = head2->next; 
		}
	}
	int* e = myor.creat();
	order(e, whf);
}
void myand(BST &p,Graph &whf,string a, string b)  //对a,b两个节点的链表进行与操作，结果加到一个新的链表mylist中
{
	BST q1 = p;
	BST q2 = p;
	Node *head1 = find(q1, a)->next;
	Node *head2 = find(q2, b)->next;
	list myand;
	while (head1 != NULL&&head2 != NULL)
	{
		if (head1->Data > head2->Data)
			head1 = head1->next;
		else if (head1->Data < head2->Data)
			head2 = head2->next;
		else
		{
			myand.insertlist(head1->Data);
			head1 = head1->next;
		}
	}

	int* e = myand.creat();
	//return e;
	order(e, whf);
}




///////////////////////////////////////字符串的操作///////////////////////////////////////////////////
void checkName(string& line)		//处理掉单词中的除字母外的字符
{
	int l = line.length();
	for (int k = 0; k < l; k++)
	{
		if (line[k] < 65 || (line[k]>90 && line[k] < 97) || line[k]>122)
		{
			for (int j = k; j < l; j++)
				line[j] = line[j + 1];
			l--;
			k--; //此行有误，两个非法值在一起就算不出来了
		}
		if (l == 0)
		{
			line = "aaaaa";
		}
	}
}



////////////////////////////////////////主函数//////////////////////////////////////////////////
int main()
{
///////////////////////////////////////建立图whf//////////////////////////////////////////////
	ifstream fin2("e:\\link.txt");          //打开link
	Graph whf;								//建立图
	int x;	
	char c;
	int num = 0;
	int doc = 0;				 //定义论文号和被引用数，消除文件格式
	while (!fin2.eof())
	{
		fin2 >> c >> c >> num >> c >> doc >> c;          // 消除格式
		for (int i = 0; i < doc; i++)
		{
			fin2 >> x;                            //将x论文插入
			whf.Insert(num, x);
		}
	}
	cout << "succ" << endl;
	fin2.close();

//////////////////////////////////////建立二叉搜索树实现倒排索引//////////////////////////////////
	//word=3198145
	int pattern;
	int t = 0;
	int i = 0;
	BST root = NULL;
	string *word = new string[3198145];
	ifstream read;
	ofstream display;
	read.open("./documents.txt");
	//while (!read.eof())
	//{
	for (int i = 0; i < 301981; i++)
	{
		read >> word[i];
		if (word[i].substr(0, 2) == "##"&&word[i].substr(2, 1) != "#")
			t = atoi(word[i].substr(2).c_str());
		checkName(word[i]);
		insert(root, word[i], t);
		//i = i + 1;
		//cout << word[i];
		//cout << endl;
	}
	string value,value1,value2;

	while (1)
	{
		cout << "选择想实现的功能模式1为倒排索引，模式2为布尔与或并按入度输出,模式3用来测试图，输入0退出 " << endl;
		cin >> pattern;
		if (pattern == 1)
		{
			while (1)
			{
				cout << "请输入要查找的单词 ##结束 " << endl;
				cin >> value;
				if (value == "##")
					break;
				find1(root, value);
			}
		}
		else if (pattern == 2)
		{
			while (1)
			{
				cout << "请输入模式 0退出 1and 2or " << endl;
				cin >> pattern;
				if (pattern == 0)
					break;
				else if (pattern == 1)
				{
					cout << "And: " << endl;
					cin >> value1 >> value2;
					myand(root, whf, value1, value2);
				}
				else if (pattern == 2)
				{
					cout << "or: " << endl;
					cin >> value1 >> value2;
					myor(root, whf, value1, value2);
				}
				else
					continue;
			}
		}
		else if (pattern == 3)
		{
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
		else if (pattern == 0)
			break;
		else
			continue;
	}
	//cout << "中序遍历： " << endl;
	//inOrder(root);
	read.close();
	display.close();
	system("pause");
	return 0;
}
