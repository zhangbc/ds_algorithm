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


// ���ݽṹ�㷨3.5��Hanoi������
/* �ᶯ���� */
int count = 0;
void move(char x, int i, char z)
{
	cout << ++count << ". Move disk " << i << " from " << x << " to " << z << ".\n";
}


/* ������x�ϰ�ֱ����С���������϶��±��Ϊ1~n��n��Բ��
   ������ᵽ����z�ϣ�y���������������� */
void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
	{
		move(x, 1, z);   // �����Ϊ1��Բ�̴�x�ƶ���z
	}
	else
	{
		hanoi(n-1, x, z, y);  // ��x�ϱ��Ϊ1��n-1��Բ���ƶ���y, z��������
		move(x, n, z);        // �����Ϊn��Բ�̴�x�ƶ���z
		hanoi(n-1, y, x, z);  // ��y�ϱ��Ϊ1��n-1��Բ���ƶ���z, x��������
	}
}


// ���Ժ���
void TestCExercise()
{
	cout << "==============C���Ծ�������㼯��ʾ================\n" << endl;
	float pi = get_pi();
	cout << "�е�ֵΪ��" << pi << endl;
	
	cout << "\n=======Hanoi������==========\n" << endl;
	hanoi(3, 'A', 'B', 'C');
	cout << endl;
}