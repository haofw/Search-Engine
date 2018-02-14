#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;
#define Vertices 16980       //������������



//////////////////////////////////////////ͼ���ඨ��///////////////////////////////////////
struct Edge				//��
{           
	int dest;        //���ĺ�
	Edge *link;
};
struct Vertex
{
	Edge *adj;
	int data;
	char *title;
	int num;        //��ȣ����ô�����
};
class Graph			//�ڽӱ�
{            
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
		NodeTable[i].data = i + 1;
		NodeTable[i].num = 0;
		NodeTable[i].adj = NULL;
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
bool Graph::Insert(int a, int b)//�����ab
{              
	Edge *p = NodeTable[a - 1].adj;
	while (p != NULL&&p->dest != b) //Ѱ���ڽӶ���b
		p = p->link; 
	if (p != NULL)
		return false;         //�ҵ��˱ߣ�������
	p = new Edge;
	p->dest = b;
	p->link = NodeTable[a - 1].adj;
	NodeTable[a - 1].adj = p;
	NodeTable[a - 1].num++;         //��ȣ����ô�����+1
	return true;
}
void order(int *r, Graph &G)		//��һ�������е�ֵ�������
{
	for (int i = 0; i<20000 && r[i]>0; i++)
	{
		int max = i;
		for (int j = i; r[j]>0; j++)//ѭ��Ѱ�����ô������Ĳ�����˶���ֵ����ȣ��ҵ����r[i]��ֵ��r[max],������һ��ѭ���ҵڶ�������
		{
			if (G.NodeTable[r[j] - 1].num>G.NodeTable[r[max] - 1].num)
				max = j;
		}
		cout << G.NodeTable[r[max] - 1].data<<"  ���" << G.NodeTable[r[max] - 1].num << endl;
		r[max] = r[i];
	}

}




/////////////////////////////////////////������ඨ��////////////////////////////////////////
struct Node			//����ڵ�
{
	int Data;
	Node*next;
	Node(int Data) : Data(Data), next(NULL) {};
};
class list			//������
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
int list::deleteduplicate()			//ɾ���ظ�����
{
	if (head == NULL)
		return -1;
	Node *p, *q, *r;
	p = head;
	while (p)    // p���ڱ�������
	{
		q = p;
		while (q->next) // q����p����Ľ�㣬����p��ֵ�Ƚ�
		{
			if (q->next->Data == p->Data)
			{
				r = q->next; // r������Ҫɾ���Ľ��
				q->next = r->next;   // ��Ҫɾ���Ľ���ǰ�������
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return 0;
}
void list::insertlist(int num)  //ͷ�巨����
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
void list::outputlist()			//�������Ԫ��
{
	Node*current = head->next;
	while (current != NULL)
	{
		cout << current->Data << " ";
		current = current->next;
	}
	cout << endl;
}




/////////////////////////////////////////�����������Ķ��弰����////////////////////////////////////////
typedef struct node				//�����������ڵ�   �����ڵ��ֵ�����Һ��ӣ�����
{
	string value;
	struct node *left;
	struct node *right;
	list A;
	node(string value) : value(value), left(NULL), right(NULL) {};
}NODE, *BST;
void insert(BST &p, string value, int num)		//�ݹ�������ڵ�
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
void find1(BST &p, string value)		//��������ʱ�õݹ��ҵ��ڵ㲢����ڵ������
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
Node *find(BST &p, string value)			//ʵ�����ʱ�õ��ĺ��������ض������ڵ�������ͷ
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




////////////////////////////////////////����ʵ��/////////////////////////////////////////////////////
int* list::creat()				//����һ��������ڽ��и�������������
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
void myor (BST &p, Graph &whf,string a, string b)    //��a,b�����ڵ��������л����������ӵ�һ���µ�����mylist��
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
void myand(BST &p,Graph &whf,string a, string b)  //��a,b�����ڵ��������������������ӵ�һ���µ�����mylist��
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




///////////////////////////////////////�ַ����Ĳ���///////////////////////////////////////////////////
void checkName(string& line)		//����������еĳ���ĸ����ַ�
{
	int l = line.length();
	for (int k = 0; k < l; k++)
	{
		if (line[k] < 65 || (line[k]>90 && line[k] < 97) || line[k]>122)
		{
			for (int j = k; j < l; j++)
				line[j] = line[j + 1];
			l--;
			k--; //�������������Ƿ�ֵ��һ����㲻������
		}
		if (l == 0)
		{
			line = "aaaaa";
		}
	}
}



////////////////////////////////////////������//////////////////////////////////////////////////
int main()
{
///////////////////////////////////////����ͼwhf//////////////////////////////////////////////
	ifstream fin2("e:\\link.txt");          //��link
	Graph whf;								//����ͼ
	int x;	
	char c;
	int num = 0;
	int doc = 0;				 //�������ĺźͱ��������������ļ���ʽ
	while (!fin2.eof())
	{
		fin2 >> c >> c >> num >> c >> doc >> c;          // ������ʽ
		for (int i = 0; i < doc; i++)
		{
			fin2 >> x;                            //��x���Ĳ���
			whf.Insert(num, x);
		}
	}
	cout << "succ" << endl;
	fin2.close();

//////////////////////////////////////��������������ʵ�ֵ�������//////////////////////////////////
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
		cout << "ѡ����ʵ�ֵĹ���ģʽ1Ϊ����������ģʽ2Ϊ������򲢰�������,ģʽ3��������ͼ������0�˳� " << endl;
		cin >> pattern;
		if (pattern == 1)
		{
			while (1)
			{
				cout << "������Ҫ���ҵĵ��� ##���� " << endl;
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
				cout << "������ģʽ 0�˳� 1and 2or " << endl;
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
	//cout << "��������� " << endl;
	//inOrder(root);
	read.close();
	display.close();
	system("pause");
	return 0;
}
