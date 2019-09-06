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


// 数据结构算法3.5：Hanoi塔问题
/* 搬动操作 */
int count = 0;
void move(char x, int i, char z)
{
	cout << ++count << ". Move disk " << i << " from " << x << " to " << z << ".\n";
}


/* 将塔座x上按直径由小到大且自上而下编号为1~n的n个圆盘
   按规则搬到塔座z上，y可用作辅助塔座。 */
void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
	{
		move(x, 1, z);   // 将编号为1的圆盘从x移动到z
	}
	else
	{
		hanoi(n-1, x, z, y);  // 将x上编号为1至n-1的圆盘移动到y, z做辅助塔
		move(x, n, z);        // 将编号为n的圆盘从x移动到z
		hanoi(n-1, y, x, z);  // 将y上编号为1至n-1的圆盘移动到z, x做辅助塔
	}
}


// 测试函数
void TestCExercise()
{
	cout << "==============C语言经典问题汇集演示================\n" << endl;
	float pi = get_pi();
	cout << "π的值为：" << pi << endl;
	
	cout << "\n=======Hanoi塔问题==========\n" << endl;
	hanoi(3, 'A', 'B', 'C');
	cout << endl;
}