#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;
struct Node
{
	int Data;
	Node*next;
	Node(int Data) : Data(Data), next(NULL) {};
};
class list
{
	Node*head;
public:
	list() { head = NULL; }
	void insertlist(int aData, int bData);
	void deletelist(int aData);
	void outputlist();
	int deleteduplicate();
	Node*gethead() { return head; }
};
int list::deleteduplicate()
{
	if (head == NULL)
		return -1;
	Node *p, *q, *r;
	//p=head->next;  //delete this line // Replace with this line
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
void list::insertlist(int aData, int bData)  //设aData是结点a中的数据，bData是结点b中的数据
{
	Node*p, *q, *s;        //p指向结点a，q指向结点a_k，s指向结点b
	s = new Node(aData);  //动态分配一个新结点
	s->Data = bData;   //设b为此结点
	p = head;
	q = NULL;
	if (head == NULL)  //若是空表，使b作为第一个结点
	{
		head = s;
		s->next = NULL;
	}
	else
		if (p->Data == aData)   //若a是第一个结点
		{
			s->next = p;
			head = s;
		}
		else
		{
			while (p->Data != aData && p->next != NULL)//查找结点a
			{
				q = p;
				p = p->next;
			}
			if (p->Data == aData)     ///若有结点a
			{
				q->next = s;
				s->next = p;
			}
			else                    //若没有结点a；
			{
				p->next = s;
				s->next = NULL;
			}
		}
}
void list::deletelist(int aData)  //设aData是要删除的结点a中的数据成员
{
	Node*p, *q;            //p用于指向结点a,q用于指向结a的前一个结点
	p = head;
	q = NULL;
	if (p == NULL)  //若是空表
		return;
	if (p->Data == aData)  //若a是第一个结点
	{
		head = p->next;
		delete p;
	}
	else
	{
		while (p->Data != aData&&p->next != NULL)  //查找结点a
		{
			q = p;
			p = p->next;
		}
		if (p->Data == aData)    //若有结点a
		{
			q->next = p->next;
			delete p;
		}
	}
}
void list::outputlist()
{
	Node*current = head;
	while (current != NULL)
	{
		cout << current->Data << " ";
		current = current->next;
	}
	cout << endl;
}
typedef struct node
{
	string value;
	struct node *left;
	struct node *right;
	list A;
	node(string value) : value(value), left(NULL), right(NULL) {};
}NODE, *BST;
void insert(BST &p, string value,int num)
{
	if (p == NULL)
	{
		p = new NODE(value);
		p->A.insertlist(NULL, num);

	}
	else
	{
		if (value < p->value)
			insert(p->left, value,num);
			
		else if (value > p->value)
			insert(p->right, value,num);
		else
		{
			p->A.insertlist(NULL, num);
			//cout << "duplicate" << endl;
		}
	}
}
void inOrder(BST p)
{
	if (p != NULL)
	{
		inOrder(p->left);
		cout << p->value << "->";
		p->A.deleteduplicate();
		p->A.outputlist();
		inOrder(p->right);
	}
}
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
void find(BST &p, string value)
{
	if (p == NULL)
		cout << "error" << endl;
	else if (value < p->value)
		find(p->left, value);
	else if (value > p->value)
		find(p->right, value);
	else
	{
		p->A.deleteduplicate();
		p->A.outputlist();
	}

}
void checkName(string& line)
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
			line = "whf";
		}
	}
}
int main()
{
	//word=3198145
	int t = 0;
	BST root = NULL;
	string *word = new string[10000];
	ifstream read;
	ofstream display;
	read.open("./documents.txt");
	/*while (!read.eof())
	{
	read >> word[t];
	t = t + 1;
	}*/
	for (int i = 0; i< 1000; i++)
		read >> word[i];
	for (int i = 0; i < 1000; i++)
	{
		if (word[i].substr(0, 2) == "##"&&word[i].substr(2, 1) != "#")
			t = atoi(word[i].substr(2).c_str());
		
		checkName(word[i]);


		insert(root, word[i],t);
		//cout << word[i];
		//cout << endl;
	}
	string value;
	cout << "input: " << endl;
	cin >> value;
	find(root, value);
	//cout << "中序遍历： " << endl;
	//inOrder(root);
	read.close();
	display.close();
	system("pause");
	return 0;
}
