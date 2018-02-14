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
	list()
	{
		head = NULL;
		head = new Node(NULL);
	}
	void insertlist(int num);
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
void list::insertlist(int num)  //设aData是结点a中的数据，bData是结点b中的数据
{
	Node *p, *q;

	p = new Node(num);
	p->next = head->next;
	head->next = p;
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
void main()
{
	list A, B;
	
	int val;
	for (int i = 0; i < 9; i++)
	{
		cin >> val;
		A.insertlist(val);

	}
	A.deleteduplicate();
	cout << "\n链表A:";
	A.outputlist();

}

