// data_structure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "data_structure.h"
#include "c_exercise.h"

#include <iostream>
using namespace std;


void Print()
{
	cout << "启动程序编号说明：\n" << endl;
	cout << "1：内部排序\t\t2：C经典问题\t\t3：顺序线性表\n";
	cout << "4：链式线性表\t\t5：顺序栈\t\t6：队列\n";
	cout << "7：串\t\t0：退出\n";
}


void SwitchProgram()
{
	int sno;
	while(true)
	{
		cout << "\n请输入想要启动的程序编号(1~7)：";
		cin >> sno;
		if(sno == 0)
		{
			exit(OVERFLOW);
		}

		switch(sno)
		{
		case 1:
			TestInnerSort();
			break;
		case 2:
			TestCExercise();
			break;
		case 3:
			TestLinearListSq();
			break;
		case 4:
			TestLinearLinkList();
			break;
		case 5:
			TestStack();
			break;
		case 6:
			TestQueue();
			break;
		case 7:
			TestStrings();
			break;
		default:
			cout << "输入有误, 请重新输入!  ";
			Print();
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	Print();
	SwitchProgram();
	return 0;
}
