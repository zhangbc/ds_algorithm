#include "stdafx.h"
#include "c_exercise.h"

#include <iostream>
using namespace std;


// 求π的值
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


// 测试函数
void TestCExercise()
{
	cout << "==============C语言经典问题汇集演示================\n" << endl;
	float pi = get_pi();
	cout << "π的值为：" << pi << endl;
}