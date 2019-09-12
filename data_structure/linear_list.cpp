#include "stdafx.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct
{
	ElemType *elem;   // 存储空间基址
	int length;		  // 当前长度
	int listsize;	  // 当前分配的存储空间(以sizeof(ElemType)为单位)
}SeqList;			  // 线性表的动态分配顺序存储结构


// 算法2.3，顺序线性表初始化
/* 构造一个空的线性表L */
Status InitList_Sq(SeqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
	{
		exit(OVERFLOW);
	}

	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}


// 获取顺序线性表的长度 
int ListLength_Sq(SeqList L)
{
	return L.length > 0 ? L.length : 0;
}


// 销毁顺序线性表
Status DestroyList_Sq(SeqList &L)
{
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}


// 清空顺序线性表
Status ClearList_Sq(SeqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
	{
		exit(OVERFLOW);
	}

	L.length = 0;
	return OK;
}


// 判断顺序线性表是否为空
Status ListEmpty_Sq(SeqList L)
{
	return L.length == 0 ? TRUE : FALSE;
}


// 遍历顺序线性表
void visit(ElemType e)
{
	cout << e << " ";
}


Status ListTraverse_Sq(SeqList L, void(*visit)(ElemType))
{
	int i;
	ElemType *p;
	p = L.elem;
	for(i = 1; i <= L.length; i++)
	{
		visit(*p++);
	}
	
	cout << endl;
	return OK;
}


// 获取顺序线性表中第i个数据元素的值，并用e返回 
Status GetElem_Sq(SeqList L, int i, ElemType &e)
{
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // i值不合法
	}
	
	e = *(L.elem + i - 1);
	return OK; 
}

// 算法2.4，顺序线性表插入元素
/* 在顺序表L中第i个位置之前插入新的元素e，i的合法值为1<=i<=ListLength_Sq(L) + 1 */
Status ListInsert_Sq(SeqList &L, int i, ElemType e)
{
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // i值不合法
	}

	if(L.length >= L.listsize)  // 当前存储空间已满，增加分配
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)
		{
			exit(OVERFLOW);
		}
		
		L.elem = newbase;              // 新基址
		L.listsize += LISTINCREMENT;   // 增加存储容量
	}

	q = &(L.elem[i - 1]);
	for(p = &(L.elem[L.length - 1]); p >= q; --p)
	{
		*(p + 1) = *p;
	}

	*q = e;
	L.length++;
	return OK;
}


// 算法2.5，顺序线性表删除元素
/* 在顺序表L中删除第i个元素，并用e返回，i的合法值为1<=i<=ListLength_Sq(L) + 1 */
Status ListDelete_Sq(SeqList &L, int i, ElemType &e)
{
	ElemType *p, *q;
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // i值不合法
	}

	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for(++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}

	L.length--;
	return OK;
}


// 比较两个元素是否相等
Status compare(ElemType x, ElemType y)
{
	return x == y;
}


// 算法2.6，顺序线性表查找元素
/* 在顺序表L中查找第1个值与e满足compare()的元素的位序 */
Status LocateElem_Sq(SeqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	int i = 1;      // i的初值为第1个元素的位序
	ElemType *p;
	p = L.elem;		// p的初值为第1个元素的存储位置
	while(i <= L.length && !(*compare)(*p++, e))
	{
		i++;
	}

	if(i < L.length)
	{
		return i;
	}
	else 
	{
		return 0;
	}
}


// 将一个数组赋值给顺序线性表
Status InsertSeqList(SeqList &L, ElemType *elems, int length)
{
	if(length < 0 || elems == NULL)
	{
		cout << "empty array!" << endl;
		exit(OVERFLOW);
	}

	InitList_Sq(L);
	for(int i = 1; i <= length; i++)
	{
		ListInsert_Sq(L, i, elems[i-1]);
	}
	
	return OK;
}

// 算法2.1，合并两个线性表即A=A∪B
/* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
void UnionList(SeqList &La, SeqList Lb)
{
	// 求线性表的长度
	La.length = ListLength_Sq(La);
	Lb.length = ListLength_Sq(Lb);
	ElemType e;
	for(int i = 1; i <= Lb.length; i++)
	{
		GetElem_Sq(Lb, i, e);    // 取Lb中第i个数据元素赋给e
		if(!LocateElem_Sq(La, e, compare))
		{
			ListInsert_Sq(La, La.length+1, e);
		}
	}
}


// 算法2.2，合并两个非递减线性表
/* 已知线性表La和Lb中的数据元素按值非递减排列，
   归并La和Lb得到新的线性表Lc，其数据元素也按照值非递减排列。*/
void MergeList(SeqList La, SeqList Lb, SeqList &Lc)
{
	int i = 1, j = 1, k = 0;
	InitList_Sq(Lc);
	
	// 求线性表的长度
	La.length = ListLength_Sq(La);
	Lb.length = ListLength_Sq(Lb);
	
	ElemType ai, bj;
	while(i <= La.length && j <= Lb.length)  // La和Lb均非空
	{
		GetElem_Sq(La, i, ai);
		GetElem_Sq(Lb, j, bj);
		if(ai <= bj)
		{
			ListInsert_Sq(Lc, ++k, ai);
			i++;
		}
		else
		{
			ListInsert_Sq(Lc, ++k, bj);
			j++;
		}
	}

	while(i <= La.length)  // La均非空
	{
		GetElem_Sq(La, i++, ai);
		ListInsert_Sq(Lc, ++k, ai);
	}

	while(j <= Lb.length)  // Lb均非空
	{
		GetElem_Sq(Lb, j++, bj);
		ListInsert_Sq(Lc, ++k, bj);
	}
}


// 算法2.7，合并两个非递减线性表
/* 已知线性表La和Lb中的数据元素按值非递减排列，
   归并La和Lb得到新的线性表Lc, 其数据元素也按照值非递减排列。*/
void MergeList_Sq(SeqList La, SeqList Lb, SeqList &Lc)
{
	ElemType *pa, *pa_last, *pb, *pb_last, *pc;
	InitList_Sq(Lc);
	Lc.length = La.length + Lb.length;
	Lc.listsize = La.length + Lb.length;
	pa = La.elem;
	pb = Lb.elem;
	pc = Lc.elem;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;

	while(pa <= pa_last && pb <= pb_last)  // La和Lb均非空
	{
		*pc++ = *pa <= *pb ? *pa++ : *pb++;
	}

	while(pa <= pa_last)  // La均非空
	{
		*pc++ = *pa++;
	}

	while(pb <= pb_last)  // Lb均非空
	{
		*pc++ = *pb++;
	}
}


// 顺序线性表基本操作具体实现实例
void DisplaySeqList()
{
	SeqList L;
	cout << "初始化线性表L中……" << endl;
	InitList_Sq(L);

	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_Sq(L) << endl;

	cout << "\n线性表L插入元素……" << endl;
	ListInsert_Sq(L, 1, 0);
	ListInsert_Sq(L, 2, 1);
	ListInsert_Sq(L, 3, 2);
	ListInsert_Sq(L, 4, 3);
	ListInsert_Sq(L, 5, 4);
	ListInsert_Sq(L, 6, 5);
	ListInsert_Sq(L, 7, 6);

	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_Sq(L) << endl;
	cout << "\n线性表L表长为：" << ListLength_Sq(L) << endl;

	cout << "\n遍历线性表L：";
	ListTraverse_Sq(L, visit);

	ElemType e = NULL;
	ListDelete_Sq(L, 7, e);
	cout << "\n线性表L删除元素：" << e << endl;
	cout << "删除后, 遍历线性表L：";
	ListTraverse_Sq(L, visit);

	cout << "\n在线性表L查找值为23的元素，并返回其位置(0表示没有找到)：" << LocateElem_Sq(L, 23, compare) << endl;
	
	GetElem_Sq(L, 5, e);
	cout << "\n获取表中第5个元素(0表示没有):" << e << endl;

	ClearList_Sq(L);
	cout << "\n清空线性表L..." << endl;
	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_Sq(L) << " 表空间大小：" << L.listsize << endl;

	DestroyList_Sq(L);
	cout << "\n销毁线性表L..." << endl;
	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_Sq(L) << " 表空间大小：" << L.listsize << endl << endl;
}


// 测试函数
void TestLinearListSq()
{
	cout << "==============线性表基本操作及其相关算法演示================\n" << endl;
	cout << "==============顺序线性表基本操作具体实现实例================\n" << endl; 
	DisplaySeqList();
	
	cout << "==============合并两个线性表即A=A∪B================" << endl; 
	SeqList La, Lb, Lc;
	int elemA[] = {3, 5, 8, 11};
	int elemB[] = {2, 6, 8, 9, 11, 15, 20};
	int lengthA = sizeof(elemA)/sizeof(elemA[0]);
	int lengthB = sizeof(elemB)/sizeof(elemB[0]);
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	cout << "遍历线性表La：";
	ListTraverse_Sq(La, visit);
	cout << "遍历线性表Lb：";
	ListTraverse_Sq(Lb, visit);

	cout << "============将所有在线性表Lb中但不在La中的数据元素插入到La中========" << endl;
	UnionList(La, Lb);
	cout << "合并后，遍历线性表La：";
	ListTraverse_Sq(La, visit);
	cout << "=========归并La和Lb得到新的线性表Lc,其数据元素按照值非递减排列========" << endl;
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	MergeList(La, Lb, Lc);
	cout << "合并后，遍历线性表Lc：";
	ListTraverse_Sq(Lc, visit);
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	MergeList_Sq(La, Lb, Lc);
	cout << "合并后，遍历顺序线性表Lc：";
	ListTraverse_Sq(Lc, visit);
	cout << endl;
}