// Linklist.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Linklist.h"
#include "iostream"

int main()
{
	Linklist list;
	list.AddElem(2);
	list.AddElem(9); 
	list.AddElem(9); 
	list.AddElem(5);
	list.AddElem(1);
	list.InsertElemAt(3, 5);
	list.print();
	cout << endl;
	cout << "length" << list.length << endl;
	list.print(0);
	list.DeleteElemAt(6);
	


	cout << "length" << list.length << endl;
	list.print();
	system("pause");
    return 0;
}

