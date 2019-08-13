#include "stdafx.h"
#include<limits.h>
#include "data_structure.h"

#include <iostream>
using namespace std;


#define MAXSIZE 20    // һ������ʾ����С˳������󳤶�
typedef int KeyType;  // ����ؼ��֣�����Ϊ��������
typedef int InfoType; // ����ǹؼ��֣�����Ϊ��������

typedef struct 
{
	KeyType key;        // �ؼ�����
	InfoType otherinfo; // ����������
}RedType;

typedef struct
{
	RedType *r;				 // r[0]���û������ڱ���Ԫ
	int length;				 //	˳�����
}SqList;					 // ˳�������

typedef struct
{
	RedType rc;		  // ��¼��
	int next;		  // ָ����
}SLNode;			  // ��������

typedef struct
{
	SLNode *r;		// 0�ŵ�Ԫ��ʾͷ���
	int length;		// ����ǰ����
}SLinkListType;		// ��̬��������


// ���Ա��ʼ��
Status InitSqList(SqList &L)
{	
	L.r = (RedType*)malloc((MAXSIZE + 1) * sizeof(RedType));  // r[0]���û������ڱ���Ԫ
	if(!L.r)
	{
		exit(OVERFLOW);
	}
	L.length = 0;
	return OK;
}


// ��һ�����鸳ֵ�����Ա�
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


// ���Ա����
void OutputSqList(SqList L)
{
	for(int i = 1; i <= L.length; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout <<"\n" << endl;
}


// ��̬�����ʼ��
Status InitSLinkList(SLinkListType &SL)
{	
	SL.r = (SLNode*)malloc((MAXSIZE + 1) * sizeof(SLNode));
	if(!SL.r)
	{
		exit(OVERFLOW);
	}
	SL.r[0].rc.key = INT_MAX - 1; // �洢��<limits.h>��, ��ͷ����¼�Ĺؼ���ȡ�������(�ǽ�������ı�β)
	SL.r[0].next = 0; // next��Ϊ0��ʾ��β(��Ϊ�ձ���ʼ��)
	SL.length = 0;

	return OK;
}


// ��һ�����鸳ֵ�����Ա�
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


// ��̬�������
void OutputSLinkList(SLinkListType SL)
{
	for(int i = 1; i <= SL.length; i++)
	{
		cout << SL.r[i].rc.key << "(" << SL.r[i].next << ") ";
	}
	cout <<"\n" << endl;
}


// ��������������ֵ
void swap(KeyType &a, KeyType &b)
{
	KeyType temp;
	temp = a;
	a = b;
	b = temp;
}


// �㷨10.1, ֱ�Ӳ�������
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


// �㷨10.2���۰��������
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
		for(j = i - 1; j >= high + 1; j--) // ��¼����
		{
			L.r[j + 1] = L.r[j];
		}
		L.r[high + 1] = L.r[0];
	}
}


// �㷨10.x��2-·��������
void P2InsertSort(SqList &L)
{
	int i, j;
	int first, final;
	RedType *d;
	d = (RedType*)malloc(L.length * sizeof(RedType));  // ����L.length����¼����ʱ�ռ�
	d[0] = L.r[1];
	first = final = 0;
	for(i = 2; i <= L.length; i++)
	{
		if(L.r[i].key < d[first].key)
		{
			// �����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��)
			first = (first - 1 + L.length) % L.length;
			d[first] = L.r[i];
		}
		else if (L.r[i].key > d[final].key)
		{
			// �����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��)
			final = final + 1;
			d[final] = L.r[i];
		}
		else
		{
			// �����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��)
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


// �㷨10.3�����������
/* ���ݾ�̬����SL�и�����ָ��ֵ������¼λ�ã�ʹ��SL�м�¼���ؼ��� */
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


// �㷨10.4��ϣ������
/* һ��ϣ�����������㷨���� */
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


// ���Ժ���
void test_inner_sort()
{
	cout << "==============�ڲ�������ʾ================\n" << endl;
	SqList L;
	int keys[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int length = sizeof(keys)/sizeof(keys[0]);
	

	cout << "==============ֱ�Ӳ�������================" << endl;
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	InsertSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============�۰��������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	BInsertSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============2-·��������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	P2InsertSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);
	
	cout << "==============���������================" << endl;
	RedType D[]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SLinkListType SL;
	InitSLinkList(SL);
	InsertSLinkList(SL, D, 8);
	cout << "ԭ������Ϊ��";
	OutputSLinkList(SL);
	Arrange(SL);
	cout << "����������Ϊ��";
	OutputSLinkList(SL);

	cout << "==============ϣ������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	
	int dlta[] = {5, 3, 1};
	int dlta_length = sizeof(dlta)/sizeof(dlta[0]);
	ShellSort(L, dlta, dlta_length);
	cout << "���������Ϊ��";
	OutputSqList(L);
}