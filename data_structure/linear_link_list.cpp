#include "stdafx.h"
#include "string.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;       // 线性表的单链表存储结构


typedef struct
{
	CElemType data;
	int cur;
}component, SLinkList[MAXSIZE];   // 线性表的静态单链表存储结构


typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;            // 线性表的双向链表存储结构


typedef struct    // 项的表示，多项式的项作为LinkList的数据元素
{
	float coef;      // 系数
	int expn;        // 指数
}term, N_ElemType;   // term用于Polynomial的ADT, N_ElemType为PLinkList的数据对象名


typedef struct PLNode
{
	N_ElemType data;
	struct PLNode *next;
}PLNode, *PLinkList; // 线性表的单链表存储结构


typedef PLinkList polynomial;// 用带头结点的有序链表表示多项式


// 单链表初始化
/* 构造一个空的线性表L */
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
	{
		exit(OVERFLOW);
	}

	L->next = NULL;  // 建立一个带头结点的单链表
	return OK;
}


// 获取单链表的长度 
int ListLength_L(LinkList L)
{
	LNode *p;
	p = L->next;
	int count = 0;  // 计数器
	while(p)
	{
		count++;
		p = p->next;
	}

	return count;
}


// 判断单链表是否为空
Status ListEmpty_L(LinkList L)
{
	return L->next == NULL;
}


// 遍历单链表
Status ListTraverse_L(LinkList L)
{
	LNode *p;
	p = L->next;
	while(p)
	{
	    cout << p->data;
		p = p->next;
		if(p)
		{
			cout << "->";
		}
	}
	
	cout << endl;
	return OK;
}


// 算法2.8，获取单链表中第i个数据元素的值，并用e返回
/* L为带头结点的单链表的头指针。
   当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR。*/
Status GetElem_L(LinkList L, int i, ElemType &e)
{
	LNode *p;
	int j = 1;  // 计数器
	p = L->next;  // p指向第一个结点
	while(p && j < i) // 顺指针向后查找，直到p指向第i个元素或者p为空
	{
		p = p->next;
		j++;
	}
	
	if(!p || j > i)  // 第i个元素不存在
	{
		return ERROR;
	}

	e = p->data;  // 取第i个元素
	return OK; 
}

// 算法2.9，单链表插入元素
/* 在带头结点的单链表L中第i个位置之前插入新的元素e */
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	LNode *p, *s;
	p = L;
	int j = 0;
	while(p && j < i - 1) // 寻找第i-1个结点
	{
		p = p->next;
		j++;
	}

	if(!p || j > i)
	{
		return ERROR;
	}
	
	s = (LNode*)malloc(sizeof(LNode));
	if(!s)
	{
		return ERROR;
	}

	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


// 算法2.10，单链表删除元素
/* 在带头结点的单链表L中删除第i个元素，并用e返回其值 */
Status ListDelete_L(LinkList &L, int i, ElemType &e)
{
	LNode *p, *q;
	p = L;
	int j = 0;
	while(p->next && j < i - 1) // 寻找第i个结点，并令p指向其前驱
	{
		p = p->next;
		j++;
	}

	if(!p->next || j > i - 1)  // 删除位置不合理
	{
		return ERROR;
	}
	
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}


// 算法2.11，建立单链表
/* 逆序输入n个元素的值，建立带表头结点的单链表L。*/
void CreateList_L(LinkList &L, int n)
{
	LNode *p;
	int i;
	InitList_L(L);
	
	for(i = n; i > 0; i--)
	{
		p = (LNode *)malloc(sizeof(LNode)); // 生成新结点
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}


// 比较两个元素是否相等
Status equal(ElemType x, ElemType y)
{
	return x == y;
}


// 单链表查找元素
/* 在单链表L中查找第1个值与e满足equal()的元素的位序 */
Status LocateElem_L(LinkList L, ElemType e, Status (*equal)(ElemType, ElemType))
{
	int i = 1;      // i的初值为第1个元素的位序
	LNode *p;
	p = L->next;		// p的初值为第1个元素的存储位置
	while(p && !(*equal)(p->data, e))
	{
		i++;
		p = p ->next;
	}

	return p && (*equal)(p->data, e) ? i : 0;
}


// 将一个数组赋值给单链表
Status InsertLinkList(LinkList &L, ElemType *data, int length)
{
	if(length < 0 || data == NULL)
	{
		cout << "empty array!" << endl;
		exit(OVERFLOW);
	}

	InitList_L(L);
	for(int i = 1; i <= length; i++)
	{
		ListInsert_L(L, i, data[i-1]);
	}
	
	return OK;
}


// 算法2.12，合并两个非递减线性表
/* 已知线性表La和Lb中的数据元素按值非递减排列，
   归并La和Lb得到新的线性表Lc, 其数据元素也按照值非递减排列。*/
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LNode *pa, *pb, *pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;  // 用La的头结点作为Lc的头结点

	while(pa && pb)  // La和Lb均非空
	{
		if(pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}

	}
	
	pc->next = pa ? pa : pb;
	free(Lb);
}


// 算法2.13，静态单链表查找元素
/* 在静态单链线性表L中查找第1个值为e的元素，
	若找到则返回其位序，否则返回0 */
int LocateElem_SL(SLinkList S, CElemType e)
{
	int i = S[0].cur;            // i指示表中第一个结点
	while(i && S[i].data != e)   // 在表中顺链查找
	{
		i = S[i].cur;
	}

	return i;
}


// 算法2.14，将整个数组空间初始化成一个备用链表
/* 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针，
   "0"表示空指针。 */
void InitSpace_SL(SLinkList &space)
{
	for(int i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
	}

	space[MAXSIZE - 1].cur = 0;
}


// 算法2.15，从备用空间取得一个结点
/* 若备用空间链表非空，则返回分配的结点下标，否则返回0。*/
int Malloc_SL(SLinkList &space)
{
	int i = space[0].cur; 
	if(i)
	{
		space[0].cur = space[i].cur;
	}

	return i;
}


// 算法2.16，将空闲结点链接到备用链表上
/* 将下标为k的空闲结点回收到备用链表 */
void Free_SL(SLinkList &space, int k)      
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}


// 遍历静态单链表
Status ListTraverse_SL(SLinkList &L)
{
	int i = L[1].cur;	// i指示表中第一个结点
	while(i)
	{
	    cout << L[i].data << "[" << L[i].cur << "] ";
		i = L[i].cur;
	}
	
	cout << endl;
	return OK;
}

// 算法2.17，实现集合运算(A-B)∪(B-A)
/* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A)
   的静态链表，S为其头指针，假设备用空间足够大，space[0].cur为其头指针.
   例题：A={c,b,e,g,f,d},B={a,b,n,f} */
void UnionDifference(SLinkList &space)
{
	int r, p, k, i;
	InitSpace_SL(space);
	int S = Malloc_SL(space);
    r = S;   // r指向S的当前最后结点
	int m, n, j;
	CElemType e;
	cout << "依次输入A和B的元素个数: ";
	cin >> m >> n;  // 输入A和B的元素个数
	
	for(j = 1; j <= m; j++)  // 建立A的链表
	{
		i = Malloc_SL(space); // 分配结点
 		cin >> space[i].data; // 输入A的元素值
		space[r].cur = i;     // 插入到表尾
		r = i;
	}
	space[r].cur = 0;  // 尾结点的指针为空
	
	/* 依次输入B的元素值，若不在当前表中，则插入；否则删除 */
	for(j = 1; j <= n; j++) 
	{
		cin >> e;
		p = S;
		k = space[p].cur;  // k指向集合A中第一个结点
		while(k != space[r].cur && space[k].data != e) 
		{
			p = k;
			k = space[k].cur;
		}
		
		/* 当前表中不存在该元素，插入在r所指结点之后，且r的位置不变 */
		if(k == space[r].cur) 
		{
			i = Malloc_SL(space);
			space[i].data = e;
			space[i].cur = space[r].cur;
			space[r].cur = i;
		}
		else  // 该元素已在表中，删除之
		{
			space[p].cur = space[k].cur;
			Free_SL(space, k);
			if(r == k)
			{
				r = p; // 若删除的是r所指结点，则需要修改尾指针
			}
		}
	}
}


// 双向链表初始化
/* 构造一个空的线性表L */
Status InitList_DuL(DuLinkList &L)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));
	if(!L)
	{
		exit(OVERFLOW);
	}
	
	L->prior = L;
	L->next = L;  
	return OK;
}


// 判断单链表是否为空
Status ListEmpty_DuL(DuLinkList L)
{
	return L->next == L;
}


// 获取带头结点的双向链表的长度 
int ListLength_DuL(DuLinkList L)
{
	DuLNode *p;
	p = L->next;
	int count = 0;  // 计数器
	while(p != L)
	{
		count++;
		p = p->next;
	}

	return count;
}


// 获取带头结点的双向链表第i个数据元素的结点
DuLNode *GetElemP_DuL(DuLinkList L, int i)
{	
	DuLNode *p;
	int length, j = 1;
	length = ListLength_DuL(L);

	if(i < 1 || i > length + 1)
	{
		return NULL;   // i值不合法
	}
	
	p = L->next;
	while(p != L && j < i)
	{
		p = p->next;
		j++;
	}
	
	return p;
}


// 遍历双向链表
Status ListTraverse_DuL(DuLinkList L)
{
	DuLNode *p;
	p = L->next;
	while(p != L)
	{
	    cout << p->data;
		p = p->next;
		if(p != L)
		{
			cout << " <-> ";
		}
	}
	
	cout << endl;
	return OK;
}


// 算法2.18，双向链表插入元素
/* 在带头结点的双向循环链表L中第i个位置之前插入新的元素e,
   i的合法值为1<=i<=L.length+1 */
Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{
	DuLNode *s, *p;
	int j = 0;
	p = GetElemP_DuL(L, i);  // 在L中确定插入位置
	if(!p)                   // p=NULL，即插入位置不合法
	{
		return ERROR;
	}
	
	s = (DuLNode *)malloc(sizeof(DuLNode));
	if(!s)
	{
		return ERROR;
	}

	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}


// 算法2.19，双向链表删除元素
/* 在带头结点的双向循环链表L中删除第i个元素，并用e返回其值,
   i的合法值为1<=i<=L.length+1。*/
Status ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
	DuLNode *p;
	p = GetElemP_DuL(L, i);  // 在L中确定第i个元素的位置指针p
	if(!p)                   // p=NULL，即删除位置不合法
	{
		return ERROR;
	}
	
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}


// 算法2.20和算法2.21，分别参见算法2.9和算法2.12


// 算法2.22，抽象数据类型Polynomial的实现
/* 依据a的指数值<(或=)(或>)b的指数值，分别返回-1,0和1 */
Status cmp(term a, term b)
{
	int result = 0;
	if(a.expn < b.expn)
	{
		result = -1;
	}
	else if(a.expn == b.expn)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}

	return result;
}


/* 初始化 */
Status InitList_P(PLinkList &L)
{
	L = (PLinkList)malloc(sizeof(PLNode));
	if(!L)
	{
		exit(OVERFLOW);
	}
	
	L->data.coef = 0.0;
	L->data.expn = -1;
	L->next = NULL;  // 建立一个带头结点的单链表
	return OK;
}


// 判断链表是否为空
Status ListEmpty_P(PLinkList L)
{
	return L->next == NULL;
}


// 遍历链表，即输出一元多项式
Status ListTraverse_P(polynomial L)
{	
	if(!L->next)
	{
		cout << " Empty!" << endl;
		return ERROR;
	}

	PLNode *p;
	p = L->next;
	while(p)
	{
		if(p != L->next && p->data.coef > 0)
		{
			cout << "+";
		}
		
		if(p->data.coef != 0 && !(p->data.coef == 1 && p->data.expn != 0))
		{
			if(p->data.coef == -1 && p->data.expn != 0)
			{
				cout << "-";
			}
			else
			{
				cout << p->data.coef;
			}
		}
		
		if(p->data.coef != 0 && p->data.coef != 1 
			&& p->data.coef != -1 && p->data.expn != 0)
		{
			cout << "*";
		}

		if(p->data.expn == 1)
		{
			cout << "x";
		}

		if(p->data.expn > 0 && p->data.expn != 1)
		{
			cout << "x^" << p->data.expn;
		}
		
		if(p->data.expn < 0 && p->data.expn != 1)
		{
			cout << "x^(" << p->data.expn << ")";
		}

		p = p->next;
	}
	cout << endl;

	return OK;
}


/* 给当前结点赋值 */
Status SetCurElem_P(PLNode *pLNode, N_ElemType e)
{
	pLNode->data.coef = e.coef;
	pLNode->data.expn = e.expn;
	return OK;
}


/* 生成新的结点并赋值 */
Status MakeNode_P(PLNode *pLNode, N_ElemType e)
{
	if(!pLNode)
	{
		exit(OVERFLOW);
	}

	SetCurElem_P(pLNode, e);
	pLNode->next = NULL;
	return OK;
}


/* 若有序链表L中存在与e满足判定函数cmp()取值为0的元素，则q指示L中第一个值为e的结点的位置，并返回
   TRUE，否则q指示第一个与e满足判定函数cmp()取值>0的元素的前驱的位置，并返回FASLE。 */
Status LocateElem_P(polynomial L, N_ElemType e, int &q, Status(*cmp)(N_ElemType, N_ElemType))
{
	PLNode *p;
	p = L;
	int result, count = 0;
	while(L->next)
	{
		p = L;
		L = L->next;
		count++;
		result = (*cmp)(L->data, e);
		if(result == 0)
		{
			q = count;
			return TRUE;
		}

		if(result == 1)
		{
			q = count - 1;
			return FALSE;
		}
		p = L;
	}

	q = count;
	return FALSE;
}


/* 按照有序判定函数cmp()的约定，将值为e的结点插入到有序链表L的适当位置上。*/
Status OrderInsert(polynomial &L, N_ElemType e, Status(*cmp)(N_ElemType, N_ElemType))
{
	if(e.coef == 0)
	{
		return ERROR;
	}

	PLNode *p, *q;
	int pos;
	q = (PLNode *)malloc(sizeof(PLNode));
	if(!MakeNode_P(q, e))
	{
		return ERROR;
	}
	
	LocateElem_P(L, e, pos, cmp);

	p = L;	
	while(pos > 0)
	{
		p = p->next;
		pos--;
	}

	q->next = p->next;
	p->next = q;
	return TRUE;
}


/* 输入m项的系数和指数，建立表示一元多项式的有序链表P */
void CreatePolyn(polynomial &P, int m)
{
	InitList_P(P);
	PLNode *h;
	int q;
	h = P;
	
	N_ElemType e;
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem_P(h, e);  // 设置头结点的数据元素

	int i, j;
	for(i = 1; i <=m; i++)  // 依次输入m个非零项
	{
		cin >> e.coef >> e.expn;
		j = LocateElem_P(P, e, q, cmp);
		if(!j)   // 当前链表中不存在该指数项，插入链表
		{
			OrderInsert(P, e, cmp);
		}
	}
}


// 算法2.23，一元多项式的基本运算
/* 多项式加法：Pa = Pa + Pb, 利用两个多项式的结点构成“和多项式”。*/
void AddPolyn(polynomial &Pa, polynomial &Pb)
{
	PLNode *ha, *hb, *qa, *qb;
	ha = Pa;                    // ha指向Pa的头结点
	hb = Pb;					// hb指向Pb的头结点
	qa = ha->next;				// qa指向Pa当前结点
	qb = hb->next;				// qb指向Pb当前结点
	
	N_ElemType a, b, sum;
	while(qa && qb) // qa和qb非空
	{
		a = qa->data;  // a为当前比较元素
		b = qb->data;  // b为当前比较元素
		switch(cmp(a, b))
		{
		case -1:   // 多项式PA中当前结点的指数值小
			ha = qa;
			qa = ha->next;
			break;
		case 0:     // 多项式PA和PB中当前结点的指数值相等
			sum.coef = a.coef + b.coef;
			if(sum.coef != 0.0)  // 修改多项式PA中当前结点的系数值
			{
				sum.expn = a.expn;
				SetCurElem_P(qa, sum);
				ha = qa;
			}
			else             // 删除多项式PA中当前结点
			{
				ha->next = qa->next;
				free(qa);
			}
			
			hb->next = qb->next;
			qb = hb->next;
			qa = ha->next;
			break;
		case 1:  // 多项式PB中当前结点的指数值小
			OrderInsert(ha, qb->data, cmp);
			hb->next = qb->next;
			qb = hb->next;
			qa = ha->next;
			break;
		}
	}
	
	if(!ListEmpty_P(Pb)) // 链接Pb中剩余的结点
	{
		ha->next = qb;
	}
	free(hb);  // 释放Pb的头结点
}


/* 多项式加法：Pc = Pa + Pb, 利用两个多项式的结点构成“和多项式”。*/
void AddPolynT(polynomial &Pa, polynomial &Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qa指向Pa当前结点
	qb = Pb->next;				// qb指向Pb当前结点
	
	N_ElemType a, b, sum;
	while(qa && qb) // qa和qb非空
	{
		a = qa->data;  // a为当前比较元素
		b = qb->data;  // b为当前比较元素
		switch(cmp(a, b))
		{
		case -1:   // 多项式PA中当前结点的指数值小
			OrderInsert(Pc, qa->data, cmp);
			qa = qa->next;
			break;
		case 0:     // 多项式PA和PB中当前结点的指数值相等
			sum.coef = a.coef + b.coef;
			if(sum.coef != 0.0)  // 修改多项式PA中当前结点的系数值
			{
				sum.expn = a.expn;
				OrderInsert(Pc, sum, cmp);
			}			
			qb = qb->next;
			qa = qa->next;
			break;
		case 1:  // 多项式PB中当前结点的指数值小
			OrderInsert(Pc, qb->data, cmp);
			qb = qb->next;
			break;
		}
	}
	
	while(qa) // 链表Pa中剩余的结点
	{
		OrderInsert(Pc, qa->data, cmp);
		qa = qa->next;
	}

	while(qb) // 链表Pb中剩余的结点
	{
		OrderInsert(Pc, qb->data, cmp);
		qb = qb->next;
	}
}

/* 多项式减法：Pc = Pa - Pb, 利用两个多项式的结点构成“差多项式”。*/
void SubstractPolynT(polynomial Pa, polynomial Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qa指向Pa当前结点
	qb = Pb->next;				// qb指向Pb当前结点
	
	N_ElemType a, b, differ;
	while(qa && qb) // qa和qb非空
	{
		a = qa->data;  // a为当前比较元素
		b = qb->data;  // b为当前比较元素
		switch(cmp(a, b))
		{
		case -1:   // 多项式PA中当前结点的指数值小
			OrderInsert(Pc, qa->data, cmp);
			qa = qa->next;
			break;
		case 0:     // 多项式PA和PB中当前结点的指数值相等
			differ.coef = a.coef - b.coef;
			if(differ.coef != 0.0)  // 修改多项式PA中当前结点的系数值
			{
				differ.expn = a.expn;
				OrderInsert(Pc, differ, cmp);
			}			
			qb = qb->next;
			qa = qa->next;
			break;
		case 1:  // 多项式PB中当前结点的指数值小
			differ.coef = -(qb->data.coef);
			differ.expn = qb->data.expn;
			OrderInsert(Pc, differ, cmp);
			qb = qb->next;
			break;
		}
	}

	while(qa) // 链表Pa中剩余的结点
	{
		OrderInsert(Pc, qa->data, cmp);
		qa = qa->next;
	}
	
	while(qb) // 链表Pb中剩余的结点
	{
		differ.coef = -(qb->data.coef);
		differ.expn = qb->data.expn;
		OrderInsert(Pc, differ, cmp);
		qb = qb->next;
	}
}


/* 按照有序判定函数cmp()的约定，将值为e的结点合并到有序链表L的适当位置上，
   如果指数相同，则系数做加法运算并修改L中对应结点的系数，反之作为新结点插入到L中。*/
Status OrderMergeInsert(polynomial &L, N_ElemType e, Status(*cmp)(N_ElemType, N_ElemType))
{
	PLNode *p, *q, *s;
	int pos;
	q = (PLNode *)malloc(sizeof(PLNode));
	s = (PLNode *)malloc(sizeof(PLNode));
	if(!MakeNode_P(q, e))
	{
		return ERROR;
	}
	
	int k = LocateElem_P(L, e, pos, cmp);

	p = L;	
	while(pos > 1)
	{
		p = p->next;
		pos--;
	}
	
	s = p->next;  // 记录当前结点
	if (k)  // 若相等，修改L表中对应结点的系数
	{
		s->data.coef = s->data.coef + q->data.coef;
		if(s->data.coef == 0)
		{
			p->next = s->next; // 删除结点
			
		}
		else
		{
			p->next = s; // 修改结点信息
		}
	}
	else   // 若不相等，则插入新结点 
	{
		q->next = p->next;
		p->next = q;
	}

	return TRUE;
}

/* 多项式乘法：Pc = Pa * Pb, 利用两个多项式的结点构成“积多项式”。*/
void MultiplyPolynT(polynomial Pa, polynomial Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qa指向Pa当前结点
	N_ElemType e;

	while(qa)
	{	
		qb = Pb->next;			// qb指向Pb当前结点
		while(qb)
		{
			e.coef = qa->data.coef * qb->data.coef;
			e.expn = qa->data.expn + qb->data.expn;
			OrderMergeInsert(Pc, e, cmp);
			qb = qb->next;
		}
		qa = qa->next;
	}
}


// 单链表基本操作具体实现实例
void DisplayLinkList()
{
	LinkList L;
	cout << "初始化线性表L中……" << endl;
	InitList_L(L);

	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_L(L) << endl;

	cout << "\n线性表L插入元素……" << endl;
	ListInsert_L(L, 1, 0);
	ListInsert_L(L, 2, 1);
	ListInsert_L(L, 3, 2);
	ListInsert_L(L, 4, 3);
	ListInsert_L(L, 5, 4);
	ListInsert_L(L, 6, 5);
	ListInsert_L(L, 7, 6);

	cout << "线性表L是否为空? (1为空,0为非空): " << ListEmpty_L(L) << endl;
	cout << "\n线性表L表长为：" << ListLength_L(L) << endl;

	cout << "遍历线性表L：";
	ListTraverse_L(L);

	ElemType e = NULL;
	ListDelete_L(L, 4, e);
	cout << "\n线性表L删除元素：" << e << endl;
	cout << "删除后, 遍历线性表L：";
	ListTraverse_L(L);

	cout << "\n在线性表L查找值为2的元素，并返回其位置(0表示没有找到)：" << LocateElem_L(L, 2, equal) << endl;
	
	GetElem_L(L, 5, e);
	cout << "\n获取表中第5个元素(0表示没有):" << e << endl;

	cout << "\n创建线性表L中(5个元素)……" << endl;
	CreateList_L(L, 5);
	ListTraverse_L(L);
	cout << endl;
}


// 双向链表基本操作具体实现实例
void DisplayDuLinkList()
{
	DuLinkList L;
	cout << "初始化双向链表L中……" << endl;
	InitList_DuL(L);

	cout << "双向链表L是否为空? (1为空,0为非空): " << ListEmpty_DuL(L) << endl;

	cout << "\n双向链表L插入元素……" << endl;
	ListInsert_DuL(L, 1, 0);
	ListInsert_DuL(L, 2, 1);
	ListInsert_DuL(L, 3, 2);
	ListInsert_DuL(L, 4, 3);
	ListInsert_DuL(L, 5, 4);
	ListInsert_DuL(L, 6, 5);
	ListInsert_DuL(L, 7, 6);

	cout << "双向链表L是否为空? (1为空,0为非空): " << ListEmpty_DuL(L) << endl;
	cout << "\n双向链表L表长为：" << ListLength_DuL(L) << endl;

	cout << "遍历双向链表L：";
	ListTraverse_DuL(L);

	ElemType e = NULL;
	ListDelete_DuL(L, 4, e);
	cout << "\n双向链表L删除元素：" << e << endl;
	cout << "删除后, 遍历双向链表L：";
	ListTraverse_DuL(L);

	cout << endl;
}


// 测试函数
void TestLinearLinkList()
{
	cout << "==============线性表基本操作及其相关算法演示================\n" << endl;
	cout << "==============单链表基本操作具体实现实例================\n" << endl; 
	DisplayLinkList();
	
	LinkList La, Lb, Lc;
	int elemA[] = {3, 5, 8, 11};
	int elemB[] = {2, 6, 8, 9, 11, 15, 20};
	int lengthA = sizeof(elemA)/sizeof(elemA[0]);
	int lengthB = sizeof(elemB)/sizeof(elemB[0]);
	cout << "=========归并La和Lb得到新的线性表Lc,其数据元素按照值非递减排列========" << endl;
	InsertLinkList(La, elemA, lengthA);
	InsertLinkList(Lb, elemB, lengthB);
	cout << "遍历线性表La：";
	ListTraverse_L(La);
	cout << "遍历线性表Lb：";
	ListTraverse_L(Lb);
	MergeList_L(La, Lb, Lc);
	cout << "合并后，遍历单链线性表Lc：";
	ListTraverse_L(Lc);
	
	cout << "\n=========实现集合运算(A-B)∪(B-A)========" << endl;
	SLinkList space;
	UnionDifference(space);
	ListTraverse_SL(space);

	cout << "\n==============双向链表基本操作具体实现实例================\n" << endl; 
	DisplayDuLinkList();

	cout << "\n==============一元多项式的表示以及相关运算具体实现实例================\n" << endl; 
	polynomial Pa, Pb, Pc;
	int m, n;
	cout << "创建一元多项式Pa和Pb, 请分别输入多项式项数：";
	cin >> m >> n;
	CreatePolyn(Pa, m);
	CreatePolyn(Pb, n);
	cout << "遍历一元多项式Pa：";
	ListTraverse_P(Pa);
	cout << "遍历一元多项式Pb：";
	ListTraverse_P(Pb);
	AddPolynT(Pa, Pb, Pc);
	cout << "Pa+Pb后遍历新的一元多项式Pc：";
	ListTraverse_P(Pc);
	SubstractPolynT(Pa, Pb, Pc);
	cout << "Pa-Pb后遍历新的一元多项式Pc：";
	ListTraverse_P(Pc);
	MultiplyPolynT(Pa, Pb, Pc);
	cout << "Pa*Pb后遍历新的一元多项式Pc：";
	ListTraverse_P(Pc);
}
