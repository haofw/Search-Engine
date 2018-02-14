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
void list::insertlist(int aData, int bData)  //��aData�ǽ��a�е����ݣ�bData�ǽ��b�е�����
{
	Node*p, *q, *s;        //pָ����a��qָ����a_k��sָ����b
	s = new Node(aData);  //��̬����һ���½��
	s->Data = bData;   //��bΪ�˽��
	p = head;
	q = NULL;
	if (head == NULL)  //���ǿձ�ʹb��Ϊ��һ�����
	{
		head = s;
		s->next = NULL;
	}
	else
		if (p->Data == aData)   //��a�ǵ�һ�����
		{
			s->next = p;
			head = s;
		}
		else
		{
			while (p->Data != aData && p->next != NULL)//���ҽ��a
			{
				q = p;
				p = p->next;
			}
			if (p->Data == aData)     ///���н��a
			{
				q->next = s;
				s->next = p;
			}
			else                    //��û�н��a��
			{
				p->next = s;
				s->next = NULL;
			}
		}
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
			k--; //�������������Ƿ�ֵ��һ����㲻������
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
	//cout << "��������� " << endl;
	//inOrder(root);
	read.close();
	display.close();
	system("pause");
	return 0;
}
