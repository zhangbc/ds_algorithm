#include "stdafx.h"
#include "c_exercise.h"

#include <iostream>
using namespace std;


// ��е�ֵ
float get_pi()
{
	int i=1, n=1;
	float s = 0;
	while(1.0/n >= 1e-6)
	{
		s += i*(1.0/n);
		i = -i;
		n += 2;
	}
	return s*4;
}


// ���Ժ���
void TestCExercise()
{
	cout << "==============C���Ծ�������㼯��ʾ================\n" << endl;
	float pi = get_pi();
	cout << "�е�ֵΪ��" << pi << endl;
}