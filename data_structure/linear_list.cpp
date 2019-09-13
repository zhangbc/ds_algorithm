#include "stdafx.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct
{
	ElemType *elem;   // �洢�ռ��ַ
	int length;		  // ��ǰ����
	int listsize;	  // ��ǰ����Ĵ洢�ռ�(��sizeof(ElemType)Ϊ��λ)
}SeqList;			  // ���Ա�Ķ�̬����˳��洢�ṹ


// �㷨2.3��˳�����Ա��ʼ��
/* ����һ���յ����Ա�L */
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


// ��ȡ˳�����Ա�ĳ��� 
int ListLength_Sq(SeqList L)
{
	return L.length > 0 ? L.length : 0;
}


// ����˳�����Ա�
Status DestroyList_Sq(SeqList &L)
{
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}


// ���˳�����Ա�
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


// �ж�˳�����Ա��Ƿ�Ϊ��
Status ListEmpty_Sq(SeqList L)
{
	return L.length == 0 ? TRUE : FALSE;
}


// ����˳�����Ա�
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


// ��ȡ˳�����Ա��е�i������Ԫ�ص�ֵ������e���� 
Status GetElem_Sq(SeqList L, int i, ElemType &e)
{
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // iֵ���Ϸ�
	}
	
	e = *(L.elem + i - 1);
	return OK; 
}

// �㷨2.4��˳�����Ա����Ԫ��
/* ��˳���L�е�i��λ��֮ǰ�����µ�Ԫ��e��i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L) + 1 */
Status ListInsert_Sq(SeqList &L, int i, ElemType e)
{
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // iֵ���Ϸ�
	}

	if(L.length >= L.listsize)  // ��ǰ�洢�ռ����������ӷ���
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)
		{
			exit(OVERFLOW);
		}
		
		L.elem = newbase;              // �»�ַ
		L.listsize += LISTINCREMENT;   // ���Ӵ洢����
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


// �㷨2.5��˳�����Ա�ɾ��Ԫ��
/* ��˳���L��ɾ����i��Ԫ�أ�����e���أ�i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L) + 1 */
Status ListDelete_Sq(SeqList &L, int i, ElemType &e)
{
	ElemType *p, *q;
	if(i < 1 || i > L.length + 1)
	{
		return ERROR;   // iֵ���Ϸ�
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


// �Ƚ�����Ԫ���Ƿ����
Status compare(ElemType x, ElemType y)
{
	return x == y;
}


// �㷨2.6��˳�����Ա����Ԫ��
/* ��˳���L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ�� */
Status LocateElem_Sq(SeqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	int i = 1;      // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
	ElemType *p;
	p = L.elem;		// p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
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


// ��һ�����鸳ֵ��˳�����Ա�
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

// �㷨2.1���ϲ��������Ա�A=A��B
/* �����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La�� */
void UnionList(SeqList &La, SeqList Lb)
{
	// �����Ա�ĳ���
	La.length = ListLength_Sq(La);
	Lb.length = ListLength_Sq(Lb);
	ElemType e;
	for(int i = 1; i <= Lb.length; i++)
	{
		GetElem_Sq(Lb, i, e);    // ȡLb�е�i������Ԫ�ظ���e
		if(!LocateElem_Sq(La, e, compare))
		{
			ListInsert_Sq(La, La.length+1, e);
		}
	}
}


// �㷨2.2���ϲ������ǵݼ����Ա�
/* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����У�
   �鲢La��Lb�õ��µ����Ա�Lc��������Ԫ��Ҳ����ֵ�ǵݼ����С�*/
void MergeList(SeqList La, SeqList Lb, SeqList &Lc)
{
	int i = 1, j = 1, k = 0;
	InitList_Sq(Lc);
	
	// �����Ա�ĳ���
	La.length = ListLength_Sq(La);
	Lb.length = ListLength_Sq(Lb);
	
	ElemType ai, bj;
	while(i <= La.length && j <= Lb.length)  // La��Lb���ǿ�
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

	while(i <= La.length)  // La���ǿ�
	{
		GetElem_Sq(La, i++, ai);
		ListInsert_Sq(Lc, ++k, ai);
	}

	while(j <= Lb.length)  // Lb���ǿ�
	{
		GetElem_Sq(Lb, j++, bj);
		ListInsert_Sq(Lc, ++k, bj);
	}
}


// �㷨2.7���ϲ������ǵݼ����Ա�
/* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����У�
   �鲢La��Lb�õ��µ����Ա�Lc, ������Ԫ��Ҳ����ֵ�ǵݼ����С�*/
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

	while(pa <= pa_last && pb <= pb_last)  // La��Lb���ǿ�
	{
		*pc++ = *pa <= *pb ? *pa++ : *pb++;
	}

	while(pa <= pa_last)  // La���ǿ�
	{
		*pc++ = *pa++;
	}

	while(pb <= pb_last)  // Lb���ǿ�
	{
		*pc++ = *pb++;
	}
}


// ˳�����Ա������������ʵ��ʵ��
void DisplaySeqList()
{
	SeqList L;
	cout << "��ʼ�����Ա�L�С���" << endl;
	InitList_Sq(L);

	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_Sq(L) << endl;

	cout << "\n���Ա�L����Ԫ�ء���" << endl;
	ListInsert_Sq(L, 1, 0);
	ListInsert_Sq(L, 2, 1);
	ListInsert_Sq(L, 3, 2);
	ListInsert_Sq(L, 4, 3);
	ListInsert_Sq(L, 5, 4);
	ListInsert_Sq(L, 6, 5);
	ListInsert_Sq(L, 7, 6);

	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_Sq(L) << endl;
	cout << "\n���Ա�L��Ϊ��" << ListLength_Sq(L) << endl;

	cout << "\n�������Ա�L��";
	ListTraverse_Sq(L, visit);

	ElemType e = NULL;
	ListDelete_Sq(L, 7, e);
	cout << "\n���Ա�Lɾ��Ԫ�أ�" << e << endl;
	cout << "ɾ����, �������Ա�L��";
	ListTraverse_Sq(L, visit);

	cout << "\n�����Ա�L����ֵΪ23��Ԫ�أ���������λ��(0��ʾû���ҵ�)��" << LocateElem_Sq(L, 23, compare) << endl;
	
	GetElem_Sq(L, 5, e);
	cout << "\n��ȡ���е�5��Ԫ��(0��ʾû��):" << e << endl;

	ClearList_Sq(L);
	cout << "\n������Ա�L..." << endl;
	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_Sq(L) << " ��ռ��С��" << L.listsize << endl;

	DestroyList_Sq(L);
	cout << "\n�������Ա�L..." << endl;
	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_Sq(L) << " ��ռ��С��" << L.listsize << endl << endl;
}


// ���Ժ���
void TestLinearListSq()
{
	cout << "==============���Ա����������������㷨��ʾ================\n" << endl;
	cout << "==============˳�����Ա������������ʵ��ʵ��================\n" << endl; 
	DisplaySeqList();
	
	cout << "==============�ϲ��������Ա�A=A��B================" << endl; 
	SeqList La, Lb, Lc;
	int elemA[] = {3, 5, 8, 11};
	int elemB[] = {2, 6, 8, 9, 11, 15, 20};
	int lengthA = sizeof(elemA)/sizeof(elemA[0]);
	int lengthB = sizeof(elemB)/sizeof(elemB[0]);
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	cout << "�������Ա�La��";
	ListTraverse_Sq(La, visit);
	cout << "�������Ա�Lb��";
	ListTraverse_Sq(Lb, visit);

	cout << "============�����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La��========" << endl;
	UnionList(La, Lb);
	cout << "�ϲ��󣬱������Ա�La��";
	ListTraverse_Sq(La, visit);
	cout << "=========�鲢La��Lb�õ��µ����Ա�Lc,������Ԫ�ذ���ֵ�ǵݼ�����========" << endl;
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	MergeList(La, Lb, Lc);
	cout << "�ϲ��󣬱������Ա�Lc��";
	ListTraverse_Sq(Lc, visit);
	InsertSeqList(La, elemA, lengthA);
	InsertSeqList(Lb, elemB, lengthB);
	MergeList_Sq(La, Lb, Lc);
	cout << "�ϲ��󣬱���˳�����Ա�Lc��";
	ListTraverse_Sq(Lc, visit);
	cout << endl;
}