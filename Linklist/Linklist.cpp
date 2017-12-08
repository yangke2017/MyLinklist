#include "stdafx.h"
#include "Linklist.h"
#include "iostream"

Linklist::Linklist()
{
	InitLinklist();
}

void Linklist::InitLinklist()
{
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	length = 0;
}

Linklist::~Linklist()
{
	DestoryLinklist();
}

void Linklist::AddElem(elemtype data)
{
	Node* node ;
	node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = head->next;
	head->next = node;
	length++;
}

//ÈëÕ»
void Linklist::push(elemtype data)
{
	AddElem(data);
}

//³öÕ»
elemtype Linklist::pop()
{
	Node *p;
	p = head->next;
	head->next = p->next;
	return p->data;
	free(p);
}

void Linklist::InsertElemAt(elemtype data, int i)
{
	if (i < 0 || i > length)
		cout << "²åÈëÎ»ÖÃ´íÎó" << endl;
	else
	{
		Node* node ;
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		Node* pre;
		pre = head;
		
		for (int index = 0; index < i; index++)
		{
			pre = pre->next;
		}

		node->next = pre->next;
		pre->next = node;
		length++;

	}
}

void Linklist::print()
{
	Node *q, *p;
	p = q = head->next;
	while (!(q == NULL)) 
	{
		p = q;
		q = q->next;
		cout << p->data;
	}
}



void Linklist::print(int i)
{
	Node* q = head;
	Node* pre;
	int index = 0;
	while (index < i + 1 && q != NULL)
	{
		pre = q;
		q = q->next;
		index++;
	}
	cout << q->data << endl;


}

void Linklist::DestoryLinklist()
{
	Node* p, *q;
	p = head;
	while(!(p == NULL))
	{
		q = p;
		p = p->next;
		free(q);

	}
	length = 0;
	
}

void Linklist::DeleteElemAt(int i)
{
	Node *p, *q;
	q = p = head;
	
	int index = 0;
	while (index < i + 1 && (p != NULL))
	{
		q = p;
		p = p->next;
		index++;
	}
	if (p == NULL)
		cout << "É¾³ýÎ»ÖÃ´íÎó£¡" << endl;
	else
	{
		q->next = p->next;
		free(p);
		length--;
	}
}

