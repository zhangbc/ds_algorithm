#include "stdafx.h"
#include<limits.h>
#include<math.h>
#include "data_structure.h"


#include <iostream>
using namespace std;


#define SIZE 100
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
	SLNode *r;		// r[0]��ʾͷ���
	int length;		// ����ǰ����
}SLinkListType;		// ��̬��������

typedef struct
{
	KeyType *keys;					   // �ؼ�����
	InfoType otheritems;			   // ����������
	int next;
}SLCell;							   // ��̬����Ľ������

typedef struct
{
	SLCell *r;							// ��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
	int keynum;							// ��¼�ĵ�ǰ�ؼ��ָ���
	int recnum;							// ��̬����ĵ�ǰ����
}SLList;								// ��̬��������

typedef int ArrType[RADIX];				// ָ����������


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


// ��һ�����鸳ֵ����̬����
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


// ��̬�����ʼ��(��������)
Status InitSLList(SLList &SLL)
{	
	SLL.r = (SLCell*)malloc((MAXSIZE + 1) * sizeof(SLCell));
	if(!SLL.r)
	{
		exit(OVERFLOW);
	}
	SLL.r[0].keys = (KeyType*)malloc(MAX_NUM_OF_KEY * sizeof(KeyType));
	SLL.r[0].next = 1;
	SLL.keynum = 0;
	SLL.recnum = 0;

	return OK;
}

// ��һ�����鸳ֵ����̬����(��������)
Status InsertSLList(SLList &SLL, RedType D[], int n)
{	
	int i, unit, ten;  // ���Ȱ����������(ȡ��λ��ʮλ)
	for(i = 0; i < n; i++)
	{	
		unit = D[i].key % 10;
		ten = D[i].key / 10;
		SLL.r[i + 1].keys = (KeyType*)malloc(MAX_NUM_OF_KEY * sizeof(KeyType));
		SLL.r[i + 1].keys[0] = unit;
		SLL.r[i + 1].keys[1] = ten;
		SLL.r[i + 1].otheritems = D[i].otherinfo;
		SLL.r[i + 1].next = i + 2;
	}
	SLL.r[i].next = 0;  // ���һ������next��Ϊ0
	SLL.keynum = 2;
	SLL.recnum = n;
	
	return OK;
}


// ��̬�������(��������)
void OutputSLList(SLList SLL)
{
	for(int p = SLL.r[0].next; p; p=SLL.r[p].next)
	{
		cout << SLL.r[p].keys[1] << SLL.r[p].keys[0] << " ";
    }
	cout <<"\n" << endl;
}


// ��������������ֵ
void swap(RedType &a, RedType &b)
{
	RedType temp;
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


// �㷨10.3��2-·��������
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


// �㷨10.4�����������
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


// �㷨10.5��ϣ������
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


// �㷨10.6��ð�ݽ�������
void BubbleSort(SqList &L)
{
	int i, j;
	for(i = L.length; i > 0; i--)
	{
		for(j = 1; j < i; j++)
		{
			if(L.r[j].key > L.r[i].key)
			{
				swap(L.r[i], L.r[j]);
			}
		}
	}
}


// �㷨10.7�����ٽ�������
/* һ�˿��ٽ��������㷨���� */
int Partition(SqList &L, int low, int high)
{
	L.r[0] = L.r[low];
	KeyType pivotkey = L.r[low].key;
	while(low < high)
	{
		while(low < high && L.r[high].key >= pivotkey)
		{
			high--;
		}
		L.r[low] = L.r[high];
		while(low < high && L.r[low].key <= pivotkey)
		{
			low++;
		}
		L.r[low] = L.r[high];
	}
	L.r[low] = L.r[0];
	return low;
}


void QSort(SqList &L, int low, int high)
{
	int pivotloc;
	if(low < high)
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, low);
	}
}


void QuickSort(SqList &L)
{
	QSort(L, 1, L.length);
}


// �㷨10.8����ѡ������
/* ��L.r[i...L.length]��ѡ��key��С�ļ�¼, �������±�(λ��) */
int SelectMinKey(SqList L, int i)
{
	int j, min = i;
	KeyType minKey = L.r[i].key;
	for(j = i + 1; j <= L.length; j++)
	{
		if(L.r[j].key < minKey)
		{
			min = j;
			minKey = L.r[j].key;
		}
	}
	return min;
}


void SelectSort(SqList &L)
{
	int i, j;
	for(i = 1; i < L.length; i++)
	{
		j = SelectMinKey(L, i);
		if(i != j)
		{
			swap(L.r[i], L.r[j]);
		}
	}
}


// �㷨10.9������ѡ������
void TreeSort(SqList &L)
{
	int i,j, j1, k, k1, level;
	int len = L.length;
	level = (int)ceil(log(len)/log(2)) + 1; // ��ȫ�������Ĳ���
	k = (int)pow(2, level) - 1; // level����ȫ�������Ľ������
	k1 = (int)pow(2, level - 1) - 1; // level-1����ȫ�������Ľ������
	
	RedType *temp;
	temp = (RedType*)malloc(k * sizeof(RedType));

	for(i = 1; i <= len; i++) // ��L.r����Ҷ�ӽ��
	{
		temp[k1 + i -1] = L.r[i];
	}
	
	for(i = k1 + len; i < k; i++) // �������Ҷ�ӵĹؼ��ָ������
	{
		temp[i].key = INT_MAX;
	}

	j1 = k1;
	j = k;
	while(j1)
	{
		for(i = j1; i < j; i += 2)  // ����Ҷ�ӽ�㸳ֵ
		{
			if(temp[i].key < temp[i + 1].key)
			{
				temp[(i + 1) / 2 - 1] = temp[i];
			}
			else
			{
				temp[(i + 1) / 2 - 1] = temp[i + 1];
			}
		}
		j = j1;
		j1 = (j1 - 1) / 2;
	}
	
	for(i = 0; i < len; i++)
	{
		L.r[i + 1] = temp[0];  // ����ǰ��Сֵ����L.r[i]
		j1 = 0;
		for(j = 1; j < level; j++) // �������ҽ��temp[0]��Ҷ���е����j1
		{
			if(temp[2 * j1 + 1].key == temp[j1].key)
			{
				j1 = 2 * j1 + 1;
			}
			else 
			{
				j1 = 2 * j1 + 2;
			}
		}
		temp[j1].key = INT_MAX;
		while(j1)
		{
			j1 = (j1 + 1) / 2 - 1;  // ���Ϊj1�Ľ���˫�׽�����
			if(temp[2 * j1 + 1].key <= temp[2 * j1 + 2].key)
			{
				temp[j1] = temp[2 * j1 +1];
			}
			else
			{
				temp[j1] = temp[2 * j1 +2];
			}
		}
	}	
	free(temp);
}


// �㷨10.10��������
/* ��֪H.r[s...m]�м�¼�Ĺؼ��ֳ�H.r[s]�������ѵĶ��壬����H.r[s]�ؼ���ʹH.r[s...m]��Ϊ�󶥶�*/
void HeapAdjust(SqList &H, int s, int m)
{
	int j;
	RedType rc = H.r[s];
	for(j = 2 * s; j <= m; j *= 2)
	{
		if(j < m && (H.r[j].key < H.r[j + 1].key))
		{
			j++;
		}
		if(rc.key > H.r[j].key)
		{
			break;
		}
		H.r[s] = H.r[j];
		s = j;
	}
	H.r[s] = rc;
}


void HeapSort(SqList &L)
{
	int i;
	for(i = L.length / 2; i > 0; i--) // ��L.r[1...L.length]���ɴ󶥶�
	{
		HeapAdjust(L, i, L.length);
	}

	for(i = L.length; i > 1; i--)
	{
		swap(L.r[1], L.r[i]);
		HeapAdjust(L, 1, i - 1);
	}
}


// �㷨10.11���鲢����
/* һ�˹鲢�����㷨����: �������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i...n] */
void Merge(RedType SR[], RedType TR[], int i, int m, int n)
{
	int j, k;
	for(j = m + 1, k = i; i <= m && j <= n; k++) // ��SR�еļ�¼��С������TR
	{
		if(SR[i].key < SR[j].key)
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}

	while(i <= m) // ��ʣ���SR[i...m]���Ƶ�TR
	{
		TR[k++] = SR[i++]; 
	}
	
	while(j <= n) // ��ʣ���SR[j...n]���Ƶ�TR
	{
		TR[k++] = SR[j++];
	}
}


/* ��SR[s...t]�鲢����ΪTR1[s...t] */
void MSort(RedType SR[], RedType TR1[], int s, int t)
{
	int m;
	RedType TR2[MAXSIZE + 1];
	if(s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);     // �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
		MSort(SR, TR2, m + 1, t); // �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		Merge(TR2, TR1, s, m, t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
	}
}


void MergeSort(SqList &L)
{
	MSort(L.r, L.r, 1, L.length);
}


// �㷨10.12����������
/* ��̬����L��r���м�¼�Ѱ�(keys[0]...keys[i-1])����
   ����i���ؼ���keys[i]����RADIX���ӱ�ʹͬһ�ӱ��м�¼��keys[i]��ͬ��
   f[0...RADIX-1]��e[0...RADIX-1]�ֱ�ָ������ӱ��е�һ�������һ����¼��*/
void Distribute(SLCell *r, int i, ArrType &f, ArrType &e)
{
	int j, p;
	for(j = 0; j < RADIX; j++)  // �����ӱ��ʼ��Ϊ�ձ�
	{
		f[j] = 0;
		e[j] = 0;
	}

	for(p = r[0].next; p; p = r[p].next)
	{
		j = r[p].keys[i];   // ����¼�е�i���ؼ���ӳ�䵽[0...RADIX-1]
		if(!f[j])
		{
			f[j] = p;
		}
		else
		{
			r[e[j]].next = p;
		}

		e[j] = p;   // ��p��ָ�Ľ����뵽��j���ӱ���
	}

}


/* ��keys[i]��С����f[0...RADIX-1]��ָ�����ӱ��������ӳ�һ������
   e[0...RADIX-1]Ϊ�����ӱ��βָ�롣*/
void Collect(SLCell *r, int i, ArrType f, ArrType e)
{
	int j;
	for(j = 0; !f[j]; j++)  // �ҵ���һ���ǿ��ӱ�
	{
		;
	}
	
	r[0].next = f[j];  // r[0].nextָ���һ���ǿ��ӱ��е�һ�����
	int t = e[j];
	while(j < RADIX)
	{
		for(j++; !f[j]; j++)  // �ҵ���һ���ǿ��ӱ�
		{
			;
		}
		if(j < RADIX && f[j])  // ���������ǿ��ӱ�
		{
			r[t].next = f[j];
			t = e[j];
		}

		r[t].next = 0;   // tָ�����һ���ǿ��ӱ��е����һ�����
	}
}


void RadixSort(SLList &L)
{
	int i, p;
	ArrType f, e;
	for(i = 0; i < L.keynum; i++)  // �����λ�������ζԸ����ؼ��ֽ��з�����ռ�
	{
		Distribute(L.r, i, f, e);  // ��i�˷���
		Collect(L.r, i, f, e);	   // ��i���ռ�
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

	cout << "==============ð�ݽ�������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	BubbleSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============���ٽ�������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	QuickSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============��ѡ������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	SelectSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============����ѡ������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	TreeSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============������================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	HeapSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============�鲢����================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "ԭ����Ϊ��";
	OutputSqList(L);
	MergeSort(L);
	cout << "���������Ϊ��";
	OutputSqList(L);

	cout << "==============��������================" << endl;
	SLList SLL;
	InitSLList(SLL);
	RedType SD[] = {{21, 1}, {20, 2}, {19, 3}, {18, 4}, {17, 5}, {16, 6}, {15, 7}, {14, 8}, {13, 9}, {12, 10}};
	int sd_length = sizeof(SD)/sizeof(SD[0]);
	InsertSLList(SLL, SD, sd_length);
	cout << "ԭ����Ϊ��";
	OutputSLList(SLL);
	RadixSort(SLL);
	cout << "���������Ϊ��";
	OutputSLList(SLL);
}