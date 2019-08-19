#include "stdafx.h"
#include<limits.h>
#include<math.h>
#include "data_structure.h"


#include <iostream>
using namespace std;


#define SIZE 100
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
	SLNode *r;		// r[0]表示头结点
	int length;		// 链表当前长度
}SLinkListType;		// 静态链表类型

typedef struct
{
	KeyType *keys;					   // 关键字项
	InfoType otheritems;			   // 其他数据项
	int next;
}SLCell;							   // 静态链表的结点类型

typedef struct
{
	SLCell *r;							// 静态链表的可利用空间，r[0]为头结点
	int keynum;							// 记录的当前关键字个数
	int recnum;							// 静态链表的当前长度
}SLList;								// 静态链表类型

typedef int ArrType[RADIX];				// 指针数组类型


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


// 将一个数组赋值给静态链表
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


// 静态链表初始化(基数排序)
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

// 将一个数组赋值给静态链表(基数排序)
Status InsertSLList(SLList &SLL, RedType D[], int n)
{	
	int i, unit, ten;  // 优先按照最低排序(取个位和十位)
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
	SLL.r[i].next = 0;  // 最后一个结点的next置为0
	SLL.keynum = 2;
	SLL.recnum = n;
	
	return OK;
}


// 静态链表输出(基数排序)
void OutputSLList(SLList SLL)
{
	for(int p = SLL.r[0].next; p; p=SLL.r[p].next)
	{
		cout << SLL.r[p].keys[1] << SLL.r[p].keys[0] << " ";
    }
	cout <<"\n" << endl;
}


// 交换两个变量的值
void swap(RedType &a, RedType &b)
{
	RedType temp;
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


// 算法10.3，2-路插入排序
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


// 算法10.4，表插入排序
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


// 算法10.5，希尔排序
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


// 算法10.6，冒泡交换排序
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


// 算法10.7，快速交换排序
/* 一趟快速交换排序算法过程 */
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


// 算法10.8，简单选择排序
/* 在L.r[i...L.length]中选择key最小的记录, 返回其下标(位置) */
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


// 算法10.9，树形选择排序
void TreeSort(SqList &L)
{
	int i,j, j1, k, k1, level;
	int len = L.length;
	level = (int)ceil(log(len)/log(2)) + 1; // 完全二叉树的层数
	k = (int)pow(2, level) - 1; // level层完全二叉树的结点总数
	k1 = (int)pow(2, level - 1) - 1; // level-1层完全二叉树的结点总数
	
	RedType *temp;
	temp = (RedType*)malloc(k * sizeof(RedType));

	for(i = 1; i <= len; i++) // 将L.r赋给叶子结点
	{
		temp[k1 + i -1] = L.r[i];
	}
	
	for(i = k1 + len; i < k; i++) // 给多余的叶子的关键字赋无穷大
	{
		temp[i].key = INT_MAX;
	}

	j1 = k1;
	j = k;
	while(j1)
	{
		for(i = j1; i < j; i += 2)  // 给非叶子结点赋值
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
		L.r[i + 1] = temp[0];  // 将当前最小值赋给L.r[i]
		j1 = 0;
		for(j = 1; j < level; j++) // 沿树根找结点temp[0]在叶子中的序号j1
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
			j1 = (j1 + 1) / 2 - 1;  // 序号为j1的结点的双亲结点序号
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


// 算法10.10，堆排序
/* 已知H.r[s...m]中记录的关键字除H.r[s]外均满足堆的定义，调整H.r[s]关键字使H.r[s...m]成为大顶堆*/
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
	for(i = L.length / 2; i > 0; i--) // 把L.r[1...L.length]建成大顶堆
	{
		HeapAdjust(L, i, L.length);
	}

	for(i = L.length; i > 1; i--)
	{
		swap(L.r[1], L.r[i]);
		HeapAdjust(L, 1, i - 1);
	}
}


// 算法10.11，归并排序
/* 一趟归并排序算法过程: 将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n] */
void Merge(RedType SR[], RedType TR[], int i, int m, int n)
{
	int j, k;
	for(j = m + 1, k = i; i <= m && j <= n; k++) // 将SR中的记录由小到大并入TR
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

	while(i <= m) // 将剩余的SR[i...m]复制到TR
	{
		TR[k++] = SR[i++]; 
	}
	
	while(j <= n) // 将剩余的SR[j...n]复制到TR
	{
		TR[k++] = SR[j++];
	}
}


/* 将SR[s...t]归并排序为TR1[s...t] */
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
		MSort(SR, TR2, s, m);     // 递归地将SR[s..m]归并为有序的TR2[s..m]
		MSort(SR, TR2, m + 1, t); // 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		Merge(TR2, TR1, s, m, t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
	}
}


void MergeSort(SqList &L)
{
	MSort(L.r, L.r, 1, L.length);
}


// 算法10.12，基数排序
/* 静态链表L的r域中记录已按(keys[0]...keys[i-1])有序。
   按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同。
   f[0...RADIX-1]和e[0...RADIX-1]分别指向各个子表中第一个和最后一个记录。*/
void Distribute(SLCell *r, int i, ArrType &f, ArrType &e)
{
	int j, p;
	for(j = 0; j < RADIX; j++)  // 各个子表初始化为空表
	{
		f[j] = 0;
		e[j] = 0;
	}

	for(p = r[0].next; p; p = r[p].next)
	{
		j = r[p].keys[i];   // 将记录中第i个关键字映射到[0...RADIX-1]
		if(!f[j])
		{
			f[j] = p;
		}
		else
		{
			r[e[j]].next = p;
		}

		e[j] = p;   // 将p所指的结点插入到第j个子表中
	}

}


/* 按keys[i]自小到大将f[0...RADIX-1]所指各个子表依次连接成一个链表，
   e[0...RADIX-1]为各个子表的尾指针。*/
void Collect(SLCell *r, int i, ArrType f, ArrType e)
{
	int j;
	for(j = 0; !f[j]; j++)  // 找到第一个非空子表
	{
		;
	}
	
	r[0].next = f[j];  // r[0].next指向第一个非空子表中第一个结点
	int t = e[j];
	while(j < RADIX)
	{
		for(j++; !f[j]; j++)  // 找到下一个非空子表
		{
			;
		}
		if(j < RADIX && f[j])  // 链接两个非空子表
		{
			r[t].next = f[j];
			t = e[j];
		}

		r[t].next = 0;   // t指向最后一个非空子表中的最后一个结点
	}
}


void RadixSort(SLList &L)
{
	int i, p;
	ArrType f, e;
	for(i = 0; i < L.keynum; i++)  // 将最低位优先依次对各个关键字进行分配和收集
	{
		Distribute(L.r, i, f, e);  // 第i趟分配
		Collect(L.r, i, f, e);	   // 第i趟收集
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

	cout << "==============冒泡交换排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	BubbleSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============快速交换排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	QuickSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============简单选择排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	SelectSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============树形选择排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	TreeSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============堆排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	HeapSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============归并排序================" << endl;
	InitSqList(L);
	InsertSqList(L, keys, length);
	cout << "原数组为：";
	OutputSqList(L);
	MergeSort(L);
	cout << "排序后数组为：";
	OutputSqList(L);

	cout << "==============基数排序================" << endl;
	SLList SLL;
	InitSLList(SLL);
	RedType SD[] = {{21, 1}, {20, 2}, {19, 3}, {18, 4}, {17, 5}, {16, 6}, {15, 7}, {14, 8}, {13, 9}, {12, 10}};
	int sd_length = sizeof(SD)/sizeof(SD[0]);
	InsertSLList(SLL, SD, sd_length);
	cout << "原数组为：";
	OutputSLList(SLL);
	RadixSort(SLL);
	cout << "排序后数组为：";
	OutputSLList(SLL);
}