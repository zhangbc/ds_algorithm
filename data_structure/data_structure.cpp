// data_structure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "data_structure.h"
#include "c_exercise.h"

#include <iostream>
using namespace std;


void Print()
{
	cout << "����������˵����\n" << endl;
	cout << "1���ڲ�����\t\t2��C��������\t\t3��˳�����Ա�\n";
	cout << "4����ʽ���Ա�\t\t5��˳��ջ\t\t6������\n";
	cout << "7����\t\t0���˳�\n";
}


void SwitchProgram()
{
	int sno;
	while(true)
	{
		cout << "\n��������Ҫ�����ĳ�����(1~7)��";
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
			cout << "��������, ����������!  ";
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
