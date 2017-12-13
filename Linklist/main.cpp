// Linklist.cpp : �������̨Ӧ�ó������ڵ㡣
// Programming Practice
// About Data Structure and Algorithm
// Linklist and Arithmetic Expression

#include "stdafx.h"
#include "Linklist.h"
#include "iostream"
#include "string"
#include "stack"
#include "cmath"

#define name2str(name) (#name) 
#define SIZE 100
using namespace std;
float compute(string);
bool isOperator(char);
bool isNumber(char);
string getWord(string, int*);
float computMidresult(float, char, float);
int InPri(char);
int OutPri(char);
void printAll(stack<float>, stack<char>);
bool isRightEnd(string);

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
	cout << endl;

 //�������ʽ����
start:
	cout << "--------------------------------" << endl;
	cout << "�����������ʽ,�ԵȺŽ�β" << endl;
	char exp[SIZE];
	cin >> exp;
	cout << "���ʽΪ��" << exp << endl;

//test for getWord
	/*
	string str = getWord(exp, index);
	cout << str << endl;
	string str2 = getWord(exp, index);
	cout << str2 << endl;
	*/

	if (isRightEnd(exp))
	{
		float a = 0;
		a = compute(exp);
		cout << "Result: " << a << endl;
	}
	while (1)
	{
		cout << "end? Press y/n" << endl;
		string receive;
		cin >> receive;
		if (receive == "y")
		{
			goto start;
		}
		else if (receive == "n")
			return 0;
		else
			cout << "Press y/n first" << endl;
	}

	system("pause");
    return 0;
}

//�����ʽ�Ƿ��ԡ�=����β
bool isRightEnd(string exp)
{
	int temp = exp.length();
	if (exp[temp - 1] != '=')
	{
		cout << "���󣡱��ʽӦ�ԡ�=����β��" << endl;
		return false;
	}
	else
		return true;
}

// (Algorithm) �����������ʽֵ
float compute(string exp)
{
	stack<char> operators;  //�����ջ
	stack<float> number;    //������ջ
	float result = 0;       //������
	char op;                //���浯��ջ�������
	float x, y;             //���浯��ջ�Ĳ�����
	int b = 0;
	int *index = &b;        //��Ǳ��ʽɨ��λ��
	operators.push('(');    //�����ջ�׷��롮����
	while (1)               //��ʼѭ��ɨ��ÿһ�� word
	{
		string str = getWord(exp, index);
		if (str.empty())
		{
			cout << "getWord ���ؿ�ֵ��������ʽ�Ƿ��ԡ�=����β" << endl;
			return 0;
		}
		else if (isNumber(str[0]))   //�ǲ��������������ջ
		{
			int num = std::stoi(str);
			number.push(num);
		}
		else                    //������������������        
		{
			switch (str[0])
			{
			case ')':           //������ջ����ֱ������������
				while (operators.top() != '(')
				{
					if (operators.empty() || (number.size() < 2) )            //�޷�ȡ��һ�����������������
					{
						cout << ")���ʽ����" << endl;
						return 0;
					}
					else if (!(operators.top() == '/' && (number.top() == 0)))   //��ȥ����������
					{
						op = operators.top();
						operators.pop();
						x = number.top();
						number.pop();
						y = number.top();
						number.pop();
						float midresult = computMidresult(y, op, x);
						number.push(midresult);
					}
					else                                                      //���ʽ���ֳ���������
					{
						cout << ")�����" << endl;
						return 0;
					}
				}
				operators.pop();
				break;
			case '=':  //������ջֱ������ջ�׵�������Ϊֹ
				while (operators.top() != '(')
				{
					if (operators.empty() || (number.size() < 2))
					{
						cout << "=���ʽ����" << endl;
						return 0;
					}
					else if (!(operators.top() == '/' && number.top() == 0))
					{
						op = operators.top();
						operators.pop();
						x = number.top();
						number.pop();
						y = number.top();
						number.pop();
						float midresult = computMidresult(y, op, x);
						number.push(midresult);
					}
					else
					{
						cout << "=�����" << endl;
						return 0;
					}
				}
				if (number.size() == 1)
				{
					result = number.top();
					return result;
				}
				else
				{
					cout << "δ֪����" << endl;
					printAll(number, operators);
					return 0;
				}

				break;
			default:                   
				while (InPri(operators.top()) > OutPri(str[0]))  //ջ����������ȼ�����ջ����������ȼ�����ǰ����������򷴸���ջ����ֱ��ջ����������ȼ�����ջ����������ȼ�
				{
					if (operators.empty() || (number.size() < 2))
					{
						cout << "defult���ʽ����" << endl;
						return 0;
					}
					else if (!((operators.top() == '/') && number.top() == 0))
					{
						op = operators.top();
						operators.pop();
						x = number.top();
						number.pop();
						y = number.top();
						number.pop();
						float midresult = computMidresult(y, op, x);
						number.push(midresult);
					}
					else
					{
						cout << "default�����" << endl;
						printAll(number, operators);
						return 0;
					}
				}
				operators.push(str[0]);   //ջ����������ȼ�С��ջ����������ȼ�����ǰ���������ջ���������ջ
				break;
			}
		}
	}
	return 0;
}

/*

��ԭ�������������ȼ���ͬһ�����ջ�����ջ�ڣ�

�����   ջ�����ȼ�    ջ�����ȼ� 
--------------------------------
^        5            6
*��/     4            3
+��-     2            1
(        0            7
--------------------------------

*/

int InPri(char op)       //�����������ջ�����ȼ�
{
	if (op == '^')
		return 5;
	if (op == '*' || op == '/')
		return 4;
	if (op == '+' || op == '-')
		return 2;
	if (op == '(')
		return 0;
}

int OutPri(char op)     //�����������ջ�����ȼ�
{
	if (op == '^')
		return 6;
	if (op == '*' || op == '/')
		return 3;
	if (op == '+' || op == '-')
		return 1;
	if (op == ')')
		return 7;
}

float computMidresult(float x, char op, float y)    //�����Ԫ���ʽ��ֵ
{
	if (op == '+')
		return x + y;
	else if (op == '-')
		return x - y;
	else if (op == '*')
		return x * y;
	else if (op == '/')
		return x / y;
	else if (op == '^')
		return pow(x, y);
	else
	{
		cout << "�����޷����㡣" << endl;
		return NULL;
	}
}


string getWord(string exp, int *index)  //���ص���,��ָ����һ������
{
	string str = "";
	if (exp[*index] == NULL)
	{
		cout << "getWord ����" << endl;
		return str;
	}
	char data = exp.at(*index);
	if (isOperator(data))
	{
		str = str + data;
		(*index)++;
		return str;
	}
	else if (isNumber(data))
	{
		do
		{
			str = str + data;
			(*index)++;
			data = exp[*index];
		} while (isNumber(data));
		return str;
	}
	else
	{
		cout << "���ʽ���󣡴��ڴ�����ţ������֣������������" << endl;
		return str;
	}
}

bool isOperator(char c)  //�ж�c�ǲ��������
{
	string str = "+-*/()=^";
	for (int i = 0; i < str.length(); i++)
	{
		if (c == str[i])
			return true;
	}
	return false;
}

bool isNumber(char c) //�ж�c�ǲ�������
{
	int i = (int)c;
	if (i > 47 && i < 58)
		return true;
	else
		return false;

}


void printAll(stack<float> s1, stack<char> s2)  //For test:: ���������ջ�������ջ������ֵ
{
	if (s1.empty())
		cout << name2str(s1) << "Ϊ��" << endl;
	else
	{
		cout << name2str(s1) << ": ";
		while (!s1.empty())
		{
			cout << s1.top();
			s1.pop();
		}
		cout << endl;
	}

	if (s2.empty())
		cout << name2str(s2) << "Ϊ��" << endl;
	else
	{
		cout << name2str(s2) << ": ";
		while (!s2.empty())
		{
			cout << s2.top();
			s2.pop();
		}
		cout << endl;
	}
}

