#pragma once
using namespace std;
typedef int elemtype;

struct Node
{
	elemtype data;
	Node* next;
};

class Linklist
{
public:
	Linklist();
	~Linklist();
	void InitLinklist();
	void DestoryLinklist();
	//Node GetElemAt(int i);
	void print(int i);
	void AddElem(elemtype data);
	void InsertElemAt(elemtype data, int i);
	void DeleteElemAt(int i);
	void print();
	void push(elemtype data);
	elemtype pop();
	int length;
private:
	Node *head;

};

