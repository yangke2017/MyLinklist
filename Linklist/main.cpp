// Linklist.cpp : 定义控制台应用程序的入口点。
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

 //算术表达式计算
start:
	cout << "--------------------------------" << endl;
	cout << "输入算术表达式,以等号结尾" << endl;
	char exp[SIZE];
	cin >> exp;
	cout << "表达式为：" << exp << endl;

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

//检查表达式是否以“=”结尾
bool isRightEnd(string exp)
{
	int temp = exp.length();
	if (exp[temp - 1] != '=')
	{
		cout << "错误！表达式应以“=”结尾！" << endl;
		return false;
	}
	else
		return true;
}

// (Algorithm) 计算算术表达式值
float compute(string exp)
{
	stack<char> operators;  //运算符栈
	stack<float> number;    //操作数栈
	float result = 0;       //保存结果
	char op;                //保存弹出栈的运算符
	float x, y;             //保存弹出栈的操作数
	int b = 0;
	int *index = &b;        //标记表达式扫描位置
	operators.push('(');    //运算符栈底放入‘（’
	while (1)               //开始循环扫描每一个 word
	{
		string str = getWord(exp, index);
		if (str.empty())
		{
			cout << "getWord 返回空值，请检查表达式是否以“=”结尾" << endl;
			return 0;
		}
		else if (isNumber(str[0]))   //是操作数，入操作数栈
		{
			int num = std::stoi(str);
			number.push(num);
		}
		else                    //是运算符，分情况处理        
		{
			switch (str[0])
			{
			case ')':           //反复出栈处理，直到遇到左括号
				while (operators.top() != '(')
				{
					if (operators.empty() || (number.size() < 2) )            //无法取出一个运算符和两个数字
					{
						cout << ")表达式错误" << endl;
						return 0;
					}
					else if (!(operators.top() == '/' && (number.top() == 0)))   //除去除以零的情况
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
					else                                                      //表达式出现除以零的情况
					{
						cout << ")除零错！" << endl;
						return 0;
					}
				}
				operators.pop();
				break;
			case '=':  //反复出栈直到遇到栈底的左括号为止
				while (operators.top() != '(')
				{
					if (operators.empty() || (number.size() < 2))
					{
						cout << "=表达式错误！" << endl;
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
						cout << "=除零错！" << endl;
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
					cout << "未知错误！" << endl;
					printAll(number, operators);
					return 0;
				}

				break;
			default:                   
				while (InPri(operators.top()) > OutPri(str[0]))  //栈顶运算符优先级大于栈外运算符优先级（当前运算符），则反复出栈处理，直到栈外运算符优先级大于栈顶运算符优先级
				{
					if (operators.empty() || (number.size() < 2))
					{
						cout << "defult表达式错误！" << endl;
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
						cout << "default除零错" << endl;
						printAll(number, operators);
						return 0;
					}
				}
				operators.push(str[0]);   //栈顶运算符优先级小于栈外运算符优先级（当前运算符），栈外运算符入栈
				break;
			}
		}
	}
	return 0;
}

/*

（原则：四则运算优先级，同一运算符栈外高于栈内）

运算符   栈内优先级    栈外优先级 
--------------------------------
^        5            6
*，/     4            3
+，-     2            1
(        0            7
--------------------------------

*/

int InPri(char op)       //定义运算符的栈内优先级
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

int OutPri(char op)     //定义运算符的栈外优先级
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

float computMidresult(float x, char op, float y)    //计算二元表达式的值
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
		cout << "错误！无法计算。" << endl;
		return NULL;
	}
}


string getWord(string exp, int *index)  //返回单词,并指向下一个单词
{
	string str = "";
	if (exp[*index] == NULL)
	{
		cout << "getWord 出错！" << endl;
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
		cout << "表达式错误！存在错误符号（非数字，非运算符）！" << endl;
		return str;
	}
}

bool isOperator(char c)  //判断c是不是运算符
{
	string str = "+-*/()=^";
	for (int i = 0; i < str.length(); i++)
	{
		if (c == str[i])
			return true;
	}
	return false;
}

bool isNumber(char c) //判断c是不是数字
{
	int i = (int)c;
	if (i > 47 && i < 58)
		return true;
	else
		return false;

}


void printAll(stack<float> s1, stack<char> s2)  //For test:: 输出操作数栈和运算符栈的所有值
{
	if (s1.empty())
		cout << name2str(s1) << "为空" << endl;
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
		cout << name2str(s2) << "为空" << endl;
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

