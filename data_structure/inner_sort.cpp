#include "stdafx.h"
#include<limits.h>
#include "data_structure.h"

#include <iostream>
using namespace std;


#define MAXSIZE 20    // 一个用作示例的小顺序表的最大长度
typedef int KeyType;  // 定义关键字，类型为整数类型
typedef int InfoType; // 定义非关键字，类型为整数类型

typedef struct 
{
	KeyType key;        // 关键字项
	InfoType otherinfo; // 其他数据项
}RedType;

typedef struct
{
	RedType *r;				 // r[0]闲置或用作哨兵单元
	int length;				 //	顺序表长度
}SqList;					 // 顺序表类型

typedef struct
{
	RedType rc;		  // 记录项
	int next;		  // 指针项
}SLNode;			  // 表结点类型

typedef struct
{
	SLNode *r;		// 0号单元表示头结点
	int length;		// 链表当前长度
}SLinkListType;		// 静态链表类型


// 线性表初始化
Status InitSqList(SqList &L)
{	
	L.r = (RedType*)malloc((MAXSIZE + 1) * sizeof(RedType));  // r[0]闲置或用作哨兵单元
	if(!L.r)
	{
		exit(OVERFLOW);
	}
	L.length = 0;
	return OK;
}


// 将一个数组赋值给线性表
Status InsertSqList(SqList &L, KeyType *keys, int length)
{	
	if(length < 0 || keys == NULL)
	{
		cout << "empty array!" << endl;
		exit(OVERFLOW);
	}
	
	if(length > MAXSIZE)
	{
		length = MAXSIZE;
		cout << "Giving the length of keys is too long, get top " << MAXSIZE << " !" << endl;
	}

	InitSqList(L);
	cout << "The length of keys is " << length << " !" << endl;
	for(int i = 1; i <= length; i++)
	{
		L.r[i].key = keys[i - 1];
		L.length ++;
	}
	
	return OK;
}


// 线性表输出
void OutputSqList(SqList L)
{
	for(int i = 1; i <= L.length; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout <<"\n" << endl;
}


// 静态链表初始化
Status InitSLinkList(SLinkListType &SL)
{	
	SL.r = (SLNode*)malloc((MAXSIZE + 1) * sizeof(SLNode));
	if(!SL.r)
	{
		exit(OVERFLOW);
	}
	SL.r[0].rc.key = INT_MAX - 1; // 存储在<limits.h>中, 表头结点记录的关键字取最大整数(非降序链表的表尾)
	SL.r[0].next = 0; // next域为0表示表尾(现为空表，初始化)
	SL.length = 0;

	return OK;
}


// 将一个数组赋值给线性表
Status InsertSLinkList(SLinkListType &SL, RedType D[], int n)
{	
	int i, p, q;
	for(i = 0; i < n; i++)
	{
		SL.r[i + 1].rc = D[i];
		q = 0;
		p = SL.r[0].next;
		while(SL.r[p].rc.key <= SL.r[i + 1].rc.key)
		{
			q = p;
			p = SL.r[p].next;
		}

		SL.r[i + 1].next = p;
		SL.r[q].next = i + 1;
	}
	SL.length = n;
	return OK;
}


// 静态链表输出
void OutputSLinkList(SLinkListType SL)
{
	for(int i = 1; i <= SL.length; i++)
	{
		cout << SL.r[i].rc.key << "(" << SL.r[i].next << ") ";
	}
	cout <<"\n" << endl;
}


// 交换两个变量的值
void swap(KeyType &a, KeyType &b)
{
	KeyType temp;
	temp = a;
	a = b;
	b = temp;
}


// 算法10.1, 直接插入排序
void InsertSort(SqList &L)
{
	int i, j;
	for(i = 2; i <= L.length; i++)
	{
		if(L.r[i].key < L.r[i - 1].key)
		{
			L.r[0] = L.r[i];
			L.r[i] = L.r[i - 1];
			for(j = i - 2; L.r[0].key < L.r[j].key; j--)
			{
				L.r[j + 1] = L.r[j];
			}
			L.r[j + 1] = L.r[0];
		}
	}
}


// 算法10.2，折半插入排序
void BInsertSort(SqList &L)
{
	int i, j;
	int low, high, mid;
	for(i = 2; i <= L.length; i++)
	{
		L.r[0] = L.r[i];  
		low = 1;
		high = i - 1;
		while(low <= high)
		{
			mid = (low + high) / 2; 
			if(L.r[i].key < L.r[i - 1].key)
			{
				high = mid - 1;
			}
			else 
			{
				low = mid + 1;
			}
		}
		for(j = i - 1; j >= high + 1; j--) // 记录后移
		{
			L.r[j + 1] = L.r[j];
		}
		L.r[high + 1] = L.r[0];
	}
}


// 算法10.x，2-路插入排序
void P2InsertSort(SqList &L)
{
	int i, j;
	int first, final;
	RedType *d;
	d = (RedType*)malloc(L.length * sizeof(RedType));  // 生成L.length个记录的临时空间
	d[0] = L.r[1];
	first = final = 0;
	for(i = 2; i <= L.length; i++)
	{
		if(L.r[i].key < d[first].key)
		{
			// 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素)
			first = (first - 1 + L.length) % L.length;
			d[first] = L.r[i];
		}
		else if (L.r[i].key > d[final].key)
		{
			// 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素)
			final = final + 1;
			d[final] = L.r[i];
		}
		else
		{
			// 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素)
			j = final++;
			while(L.r[i].key < d[j].key)
			{
				d[(j + 1) % L.length] = d[j];
				j = (j - 1 + L.length) % L.length;
			}
			d[j + 1] = L.r[i];
		}
	}

	for(i = 1; i <= L.length; i++)
	{
		L.r[i] = d[(i + first - 1) % L.length];
	}
}


// 算法10.3，表插入排序
/* 根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字 */
void Arrange(SLinkListType &SL)
{
	int p, q, i;
	SLNode temp;
	p = SL.r[0].next;
	for(i = 1; i < SL.length; i++)
	{
		while(p < i)
		{
			p = SL.r[p].next;
		}
		q = SL.r[p].next;
		if(p != i)
		{
			temp = SL.r[p];
			SL.r[p]	= SL.r[i];
			SL.r[i] = temp;
			SL.r[i].next = p;
		}
		p = q;
	}
}


// 算法10.4，希尔排序
/* 一趟希尔插入排序算法过程 */
void ShellInsert(SqList &L, int dk)
{
	int i, j;
	for(i = dk + 1; i <= L.length; i++)
	{
		if(L.r[i].key < L.r[i - dk].key)
		{
			L.r[0] = L.r[i];
			for(j = i - dk; j > 0 && (L.r[0].key < L.r[j].key); j -= dk)
			{
				L.r[j + dk] = L.r[j];
			}
			L.r[j + dk] = L.r[0];
		}
	}
}


void ShellSort(SqList &L, int dlta[], int t)
{
	int k;
	for(k = 0; k < t; k++)
	{
		ShellInsert(L, dlta[k]);
	}
}


// 测试函数
void test_inner_sort()
{
	cout << "==============内部排序演示================\n" << endl;
	SqList L;
	int keys[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int length = sizeof(keys)/sizeof(keys[0]);
	

	cout << "==============直接插入排序================" << endl;
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	InsertSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============折半插入排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	BInsertSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============2-路插入排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	P2InsertSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);
	
	cout << "==============表插入排序================" << endl;
	RedType D[]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SLinkListType SL;
	InitSLinkList(SL);
	InsertSLinkList(SL, D, 8);
	cout << "原表数组为：";
	OutputSLinkList(SL);
	Arrange(SL);
	cout << "排序后表数组为：";
	OutputSLinkList(SL);

	cout << "==============希尔排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	
	int dlta[] = {5, 3, 1};
	int dlta_length = sizeof(dlta)/sizeof(dlta[0]);
	ShellSort(L, dlta, dlta_length);
	cout << "排序后数组为：";
	OutputSqList(L);
}