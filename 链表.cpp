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
void list::insertlist(int num)  //��aData�ǽ��a�е����ݣ�bData�ǽ��b�е�����
{
	Node *p, *q;

	p = new Node(num);
	p->next = head->next;
	head->next = p;
}
void list::deletelist(int aData)  //��aData��Ҫɾ���Ľ��a�е����ݳ�Ա
{
	Node*p, *q;            //p����ָ����a,q����ָ���a��ǰһ�����
	p = head;
	q = NULL;
	if (p == NULL)  //���ǿձ�
		return;
	if (p->Data == aData)  //��a�ǵ�һ�����
	{
		head = p->next;
		delete p;
	}
	else
	{
		while (p->Data != aData&&p->next != NULL)  //���ҽ��a
		{
			q = p;
			p = p->next;
		}
		if (p->Data == aData)    //���н��a
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
			k--; //�������������Ƿ�ֵ��һ����㲻������
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
	cout << "\n����A:";
	A.outputlist();

}

