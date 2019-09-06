#include "stdafx.h"
#include "string.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;       // ���Ա�ĵ�����洢�ṹ


typedef struct
{
	CElemType data;
	int cur;
}component, SLinkList[MAXSIZE];   // ���Ա�ľ�̬������洢�ṹ


typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;            // ���Ա��˫������洢�ṹ


typedef struct    // ��ı�ʾ������ʽ������ΪLinkList������Ԫ��
{
	float coef;      // ϵ��
	int expn;        // ָ��
}term, N_ElemType;   // term����Polynomial��ADT, N_ElemTypeΪPLinkList�����ݶ�����


typedef struct PLNode
{
	N_ElemType data;
	struct PLNode *next;
}PLNode, *PLinkList; // ���Ա�ĵ�����洢�ṹ


typedef PLinkList polynomial;// �ô�ͷ�������������ʾ����ʽ


// �������ʼ��
/* ����һ���յ����Ա�L */
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
	{
		exit(OVERFLOW);
	}

	L->next = NULL;  // ����һ����ͷ���ĵ�����
	return OK;
}


// ��ȡ������ĳ��� 
int ListLength_L(LinkList L)
{
	LNode *p;
	p = L->next;
	int count = 0;  // ������
	while(p)
	{
		count++;
		p = p->next;
	}

	return count;
}


// �жϵ������Ƿ�Ϊ��
Status ListEmpty_L(LinkList L)
{
	return L->next == NULL;
}


// ����������
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


// �㷨2.8����ȡ�������е�i������Ԫ�ص�ֵ������e����
/* LΪ��ͷ���ĵ������ͷָ�롣
   ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR��*/
Status GetElem_L(LinkList L, int i, ElemType &e)
{
	LNode *p;
	int j = 1;  // ������
	p = L->next;  // pָ���һ�����
	while(p && j < i) // ˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ���pΪ��
	{
		p = p->next;
		j++;
	}
	
	if(!p || j > i)  // ��i��Ԫ�ز�����
	{
		return ERROR;
	}

	e = p->data;  // ȡ��i��Ԫ��
	return OK; 
}

// �㷨2.9�����������Ԫ��
/* �ڴ�ͷ���ĵ�����L�е�i��λ��֮ǰ�����µ�Ԫ��e */
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	LNode *p, *s;
	p = L;
	int j = 0;
	while(p && j < i - 1) // Ѱ�ҵ�i-1�����
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


// �㷨2.10��������ɾ��Ԫ��
/* �ڴ�ͷ���ĵ�����L��ɾ����i��Ԫ�أ�����e������ֵ */
Status ListDelete_L(LinkList &L, int i, ElemType &e)
{
	LNode *p, *q;
	p = L;
	int j = 0;
	while(p->next && j < i - 1) // Ѱ�ҵ�i����㣬����pָ����ǰ��
	{
		p = p->next;
		j++;
	}

	if(!p->next || j > i - 1)  // ɾ��λ�ò�����
	{
		return ERROR;
	}
	
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}


// �㷨2.11������������
/* ��������n��Ԫ�ص�ֵ����������ͷ���ĵ�����L��*/
void CreateList_L(LinkList &L, int n)
{
	LNode *p;
	int i;
	InitList_L(L);
	
	for(i = n; i > 0; i--)
	{
		p = (LNode *)malloc(sizeof(LNode)); // �����½��
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}


// �Ƚ�����Ԫ���Ƿ����
Status equal(ElemType x, ElemType y)
{
	return x == y;
}


// ���������Ԫ��
/* �ڵ�����L�в��ҵ�1��ֵ��e����equal()��Ԫ�ص�λ�� */
Status LocateElem_L(LinkList L, ElemType e, Status (*equal)(ElemType, ElemType))
{
	int i = 1;      // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
	LNode *p;
	p = L->next;		// p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
	while(p && !(*equal)(p->data, e))
	{
		i++;
		p = p ->next;
	}

	return p && (*equal)(p->data, e) ? i : 0;
}


// ��һ�����鸳ֵ��������
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


// �㷨2.12���ϲ������ǵݼ����Ա�
/* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����У�
   �鲢La��Lb�õ��µ����Ա�Lc, ������Ԫ��Ҳ����ֵ�ǵݼ����С�*/
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LNode *pa, *pb, *pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;  // ��La��ͷ�����ΪLc��ͷ���

	while(pa && pb)  // La��Lb���ǿ�
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


// �㷨2.13����̬���������Ԫ��
/* �ھ�̬�������Ա�L�в��ҵ�1��ֵΪe��Ԫ�أ�
	���ҵ��򷵻���λ�򣬷��򷵻�0 */
int LocateElem_SL(SLinkList S, CElemType e)
{
	int i = S[0].cur;            // iָʾ���е�һ�����
	while(i && S[i].data != e)   // �ڱ���˳������
	{
		i = S[i].cur;
	}

	return i;
}


// �㷨2.14������������ռ��ʼ����һ����������
/* ��һά����space�и���������һ����������space[0].curΪͷָ�룬
   "0"��ʾ��ָ�롣 */
void InitSpace_SL(SLinkList &space)
{
	for(int i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
	}

	space[MAXSIZE - 1].cur = 0;
}


// �㷨2.15���ӱ��ÿռ�ȡ��һ�����
/* �����ÿռ�����ǿգ��򷵻ط���Ľ���±꣬���򷵻�0��*/
int Malloc_SL(SLinkList &space)
{
	int i = space[0].cur; 
	if(i)
	{
		space[0].cur = space[i].cur;
	}

	return i;
}


// �㷨2.16�������н�����ӵ�����������
/* ���±�Ϊk�Ŀ��н����յ��������� */
void Free_SL(SLinkList &space, int k)      
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}


// ������̬������
Status ListTraverse_SL(SLinkList &L)
{
	int i = L[1].cur;	// iָʾ���е�һ�����
	while(i)
	{
	    cout << L[i].data << "[" << L[i].cur << "] ";
		i = L[i].cur;
	}
	
	cout << endl;
	return OK;
}

// �㷨2.17��ʵ�ּ�������(A-B)��(B-A)
/* �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)��(B-A)
   �ľ�̬����SΪ��ͷָ�룬���豸�ÿռ��㹻��space[0].curΪ��ͷָ��.
   ���⣺A={c,b,e,g,f,d},B={a,b,n,f} */
void UnionDifference(SLinkList &space)
{
	int r, p, k, i;
	InitSpace_SL(space);
	int S = Malloc_SL(space);
    r = S;   // rָ��S�ĵ�ǰ�����
	int m, n, j;
	CElemType e;
	cout << "��������A��B��Ԫ�ظ���: ";
	cin >> m >> n;  // ����A��B��Ԫ�ظ���
	
	for(j = 1; j <= m; j++)  // ����A������
	{
		i = Malloc_SL(space); // ������
 		cin >> space[i].data; // ����A��Ԫ��ֵ
		space[r].cur = i;     // ���뵽��β
		r = i;
	}
	space[r].cur = 0;  // β����ָ��Ϊ��
	
	/* ��������B��Ԫ��ֵ�������ڵ�ǰ���У�����룻����ɾ�� */
	for(j = 1; j <= n; j++) 
	{
		cin >> e;
		p = S;
		k = space[p].cur;  // kָ�򼯺�A�е�һ�����
		while(k != space[r].cur && space[k].data != e) 
		{
			p = k;
			k = space[k].cur;
		}
		
		/* ��ǰ���в����ڸ�Ԫ�أ�������r��ָ���֮����r��λ�ò��� */
		if(k == space[r].cur) 
		{
			i = Malloc_SL(space);
			space[i].data = e;
			space[i].cur = space[r].cur;
			space[r].cur = i;
		}
		else  // ��Ԫ�����ڱ��У�ɾ��֮
		{
			space[p].cur = space[k].cur;
			Free_SL(space, k);
			if(r == k)
			{
				r = p; // ��ɾ������r��ָ��㣬����Ҫ�޸�βָ��
			}
		}
	}
}


// ˫�������ʼ��
/* ����һ���յ����Ա�L */
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


// �жϵ������Ƿ�Ϊ��
Status ListEmpty_DuL(DuLinkList L)
{
	return L->next == L;
}


// ��ȡ��ͷ����˫������ĳ��� 
int ListLength_DuL(DuLinkList L)
{
	DuLNode *p;
	p = L->next;
	int count = 0;  // ������
	while(p != L)
	{
		count++;
		p = p->next;
	}

	return count;
}


// ��ȡ��ͷ����˫�������i������Ԫ�صĽ��
DuLNode *GetElemP_DuL(DuLinkList L, int i)
{	
	DuLNode *p;
	int length, j = 1;
	length = ListLength_DuL(L);

	if(i < 1 || i > length + 1)
	{
		return NULL;   // iֵ���Ϸ�
	}
	
	p = L->next;
	while(p != L && j < i)
	{
		p = p->next;
		j++;
	}
	
	return p;
}


// ����˫������
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


// �㷨2.18��˫���������Ԫ��
/* �ڴ�ͷ����˫��ѭ������L�е�i��λ��֮ǰ�����µ�Ԫ��e,
   i�ĺϷ�ֵΪ1<=i<=L.length+1 */
Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{
	DuLNode *s, *p;
	int j = 0;
	p = GetElemP_DuL(L, i);  // ��L��ȷ������λ��
	if(!p)                   // p=NULL��������λ�ò��Ϸ�
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


// �㷨2.19��˫������ɾ��Ԫ��
/* �ڴ�ͷ����˫��ѭ������L��ɾ����i��Ԫ�أ�����e������ֵ,
   i�ĺϷ�ֵΪ1<=i<=L.length+1��*/
Status ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
	DuLNode *p;
	p = GetElemP_DuL(L, i);  // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
	if(!p)                   // p=NULL����ɾ��λ�ò��Ϸ�
	{
		return ERROR;
	}
	
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}


// �㷨2.20���㷨2.21���ֱ�μ��㷨2.9���㷨2.12


// �㷨2.22��������������Polynomial��ʵ��
/* ����a��ָ��ֵ<(��=)(��>)b��ָ��ֵ���ֱ𷵻�-1,0��1 */
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


/* ��ʼ�� */
Status InitList_P(PLinkList &L)
{
	L = (PLinkList)malloc(sizeof(PLNode));
	if(!L)
	{
		exit(OVERFLOW);
	}
	
	L->data.coef = 0.0;
	L->data.expn = -1;
	L->next = NULL;  // ����һ����ͷ���ĵ�����
	return OK;
}


// �ж������Ƿ�Ϊ��
Status ListEmpty_P(PLinkList L)
{
	return L->next == NULL;
}


// �������������һԪ����ʽ
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


/* ����ǰ��㸳ֵ */
Status SetCurElem_P(PLNode *pLNode, N_ElemType e)
{
	pLNode->data.coef = e.coef;
	pLNode->data.expn = e.expn;
	return OK;
}


/* �����µĽ�㲢��ֵ */
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


/* ����������L�д�����e�����ж�����cmp()ȡֵΪ0��Ԫ�أ���qָʾL�е�һ��ֵΪe�Ľ���λ�ã�������
   TRUE������qָʾ��һ����e�����ж�����cmp()ȡֵ>0��Ԫ�ص�ǰ����λ�ã�������FASLE�� */
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


/* ���������ж�����cmp()��Լ������ֵΪe�Ľ����뵽��������L���ʵ�λ���ϡ�*/
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


/* ����m���ϵ����ָ����������ʾһԪ����ʽ����������P */
void CreatePolyn(polynomial &P, int m)
{
	InitList_P(P);
	PLNode *h;
	int q;
	h = P;
	
	N_ElemType e;
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem_P(h, e);  // ����ͷ��������Ԫ��

	int i, j;
	for(i = 1; i <=m; i++)  // ��������m��������
	{
		cin >> e.coef >> e.expn;
		j = LocateElem_P(P, e, q, cmp);
		if(!j)   // ��ǰ�����в����ڸ�ָ�����������
		{
			OrderInsert(P, e, cmp);
		}
	}
}


// �㷨2.23��һԪ����ʽ�Ļ�������
/* ����ʽ�ӷ���Pa = Pa + Pb, ������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ����*/
void AddPolyn(polynomial &Pa, polynomial &Pb)
{
	PLNode *ha, *hb, *qa, *qb;
	ha = Pa;                    // haָ��Pa��ͷ���
	hb = Pb;					// hbָ��Pb��ͷ���
	qa = ha->next;				// qaָ��Pa��ǰ���
	qb = hb->next;				// qbָ��Pb��ǰ���
	
	N_ElemType a, b, sum;
	while(qa && qb) // qa��qb�ǿ�
	{
		a = qa->data;  // aΪ��ǰ�Ƚ�Ԫ��
		b = qb->data;  // bΪ��ǰ�Ƚ�Ԫ��
		switch(cmp(a, b))
		{
		case -1:   // ����ʽPA�е�ǰ����ָ��ֵС
			ha = qa;
			qa = ha->next;
			break;
		case 0:     // ����ʽPA��PB�е�ǰ����ָ��ֵ���
			sum.coef = a.coef + b.coef;
			if(sum.coef != 0.0)  // �޸Ķ���ʽPA�е�ǰ����ϵ��ֵ
			{
				sum.expn = a.expn;
				SetCurElem_P(qa, sum);
				ha = qa;
			}
			else             // ɾ������ʽPA�е�ǰ���
			{
				ha->next = qa->next;
				free(qa);
			}
			
			hb->next = qb->next;
			qb = hb->next;
			qa = ha->next;
			break;
		case 1:  // ����ʽPB�е�ǰ����ָ��ֵС
			OrderInsert(ha, qb->data, cmp);
			hb->next = qb->next;
			qb = hb->next;
			qa = ha->next;
			break;
		}
	}
	
	if(!ListEmpty_P(Pb)) // ����Pb��ʣ��Ľ��
	{
		ha->next = qb;
	}
	free(hb);  // �ͷ�Pb��ͷ���
}


/* ����ʽ�ӷ���Pc = Pa + Pb, ������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ����*/
void AddPolynT(polynomial &Pa, polynomial &Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qaָ��Pa��ǰ���
	qb = Pb->next;				// qbָ��Pb��ǰ���
	
	N_ElemType a, b, sum;
	while(qa && qb) // qa��qb�ǿ�
	{
		a = qa->data;  // aΪ��ǰ�Ƚ�Ԫ��
		b = qb->data;  // bΪ��ǰ�Ƚ�Ԫ��
		switch(cmp(a, b))
		{
		case -1:   // ����ʽPA�е�ǰ����ָ��ֵС
			OrderInsert(Pc, qa->data, cmp);
			qa = qa->next;
			break;
		case 0:     // ����ʽPA��PB�е�ǰ����ָ��ֵ���
			sum.coef = a.coef + b.coef;
			if(sum.coef != 0.0)  // �޸Ķ���ʽPA�е�ǰ����ϵ��ֵ
			{
				sum.expn = a.expn;
				OrderInsert(Pc, sum, cmp);
			}			
			qb = qb->next;
			qa = qa->next;
			break;
		case 1:  // ����ʽPB�е�ǰ����ָ��ֵС
			OrderInsert(Pc, qb->data, cmp);
			qb = qb->next;
			break;
		}
	}
	
	while(qa) // ����Pa��ʣ��Ľ��
	{
		OrderInsert(Pc, qa->data, cmp);
		qa = qa->next;
	}

	while(qb) // ����Pb��ʣ��Ľ��
	{
		OrderInsert(Pc, qb->data, cmp);
		qb = qb->next;
	}
}

/* ����ʽ������Pc = Pa - Pb, ������������ʽ�Ľ�㹹�ɡ������ʽ����*/
void SubstractPolynT(polynomial Pa, polynomial Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qaָ��Pa��ǰ���
	qb = Pb->next;				// qbָ��Pb��ǰ���
	
	N_ElemType a, b, differ;
	while(qa && qb) // qa��qb�ǿ�
	{
		a = qa->data;  // aΪ��ǰ�Ƚ�Ԫ��
		b = qb->data;  // bΪ��ǰ�Ƚ�Ԫ��
		switch(cmp(a, b))
		{
		case -1:   // ����ʽPA�е�ǰ����ָ��ֵС
			OrderInsert(Pc, qa->data, cmp);
			qa = qa->next;
			break;
		case 0:     // ����ʽPA��PB�е�ǰ����ָ��ֵ���
			differ.coef = a.coef - b.coef;
			if(differ.coef != 0.0)  // �޸Ķ���ʽPA�е�ǰ����ϵ��ֵ
			{
				differ.expn = a.expn;
				OrderInsert(Pc, differ, cmp);
			}			
			qb = qb->next;
			qa = qa->next;
			break;
		case 1:  // ����ʽPB�е�ǰ����ָ��ֵС
			differ.coef = -(qb->data.coef);
			differ.expn = qb->data.expn;
			OrderInsert(Pc, differ, cmp);
			qb = qb->next;
			break;
		}
	}

	while(qa) // ����Pa��ʣ��Ľ��
	{
		OrderInsert(Pc, qa->data, cmp);
		qa = qa->next;
	}
	
	while(qb) // ����Pb��ʣ��Ľ��
	{
		differ.coef = -(qb->data.coef);
		differ.expn = qb->data.expn;
		OrderInsert(Pc, differ, cmp);
		qb = qb->next;
	}
}


/* ���������ж�����cmp()��Լ������ֵΪe�Ľ��ϲ�����������L���ʵ�λ���ϣ�
   ���ָ����ͬ����ϵ�����ӷ����㲢�޸�L�ж�Ӧ����ϵ������֮��Ϊ�½����뵽L�С�*/
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
	
	s = p->next;  // ��¼��ǰ���
	if (k)  // ����ȣ��޸�L���ж�Ӧ����ϵ��
	{
		s->data.coef = s->data.coef + q->data.coef;
		if(s->data.coef == 0)
		{
			p->next = s->next; // ɾ�����
			
		}
		else
		{
			p->next = s; // �޸Ľ����Ϣ
		}
	}
	else   // ������ȣ�������½�� 
	{
		q->next = p->next;
		p->next = q;
	}

	return TRUE;
}

/* ����ʽ�˷���Pc = Pa * Pb, ������������ʽ�Ľ�㹹�ɡ�������ʽ����*/
void MultiplyPolynT(polynomial Pa, polynomial Pb, polynomial &Pc)
{
	InitList_P(Pc);
	PLNode *qa, *qb;
	qa = Pa->next;				// qaָ��Pa��ǰ���
	N_ElemType e;

	while(qa)
	{	
		qb = Pb->next;			// qbָ��Pb��ǰ���
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


// �����������������ʵ��ʵ��
void DisplayLinkList()
{
	LinkList L;
	cout << "��ʼ�����Ա�L�С���" << endl;
	InitList_L(L);

	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_L(L) << endl;

	cout << "\n���Ա�L����Ԫ�ء���" << endl;
	ListInsert_L(L, 1, 0);
	ListInsert_L(L, 2, 1);
	ListInsert_L(L, 3, 2);
	ListInsert_L(L, 4, 3);
	ListInsert_L(L, 5, 4);
	ListInsert_L(L, 6, 5);
	ListInsert_L(L, 7, 6);

	cout << "���Ա�L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_L(L) << endl;
	cout << "\n���Ա�L��Ϊ��" << ListLength_L(L) << endl;

	cout << "�������Ա�L��";
	ListTraverse_L(L);

	ElemType e = NULL;
	ListDelete_L(L, 4, e);
	cout << "\n���Ա�Lɾ��Ԫ�أ�" << e << endl;
	cout << "ɾ����, �������Ա�L��";
	ListTraverse_L(L);

	cout << "\n�����Ա�L����ֵΪ2��Ԫ�أ���������λ��(0��ʾû���ҵ�)��" << LocateElem_L(L, 2, equal) << endl;
	
	GetElem_L(L, 5, e);
	cout << "\n��ȡ���е�5��Ԫ��(0��ʾû��):" << e << endl;

	cout << "\n�������Ա�L��(5��Ԫ��)����" << endl;
	CreateList_L(L, 5);
	ListTraverse_L(L);
	cout << endl;
}


// ˫�����������������ʵ��ʵ��
void DisplayDuLinkList()
{
	DuLinkList L;
	cout << "��ʼ��˫������L�С���" << endl;
	InitList_DuL(L);

	cout << "˫������L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_DuL(L) << endl;

	cout << "\n˫������L����Ԫ�ء���" << endl;
	ListInsert_DuL(L, 1, 0);
	ListInsert_DuL(L, 2, 1);
	ListInsert_DuL(L, 3, 2);
	ListInsert_DuL(L, 4, 3);
	ListInsert_DuL(L, 5, 4);
	ListInsert_DuL(L, 6, 5);
	ListInsert_DuL(L, 7, 6);

	cout << "˫������L�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << ListEmpty_DuL(L) << endl;
	cout << "\n˫������L��Ϊ��" << ListLength_DuL(L) << endl;

	cout << "����˫������L��";
	ListTraverse_DuL(L);

	ElemType e = NULL;
	ListDelete_DuL(L, 4, e);
	cout << "\n˫������Lɾ��Ԫ�أ�" << e << endl;
	cout << "ɾ����, ����˫������L��";
	ListTraverse_DuL(L);

	cout << endl;
}


// ���Ժ���
void TestLinearLinkList()
{
	cout << "==============���Ա����������������㷨��ʾ================\n" << endl;
	cout << "==============�����������������ʵ��ʵ��================\n" << endl; 
	DisplayLinkList();
	
	LinkList La, Lb, Lc;
	int elemA[] = {3, 5, 8, 11};
	int elemB[] = {2, 6, 8, 9, 11, 15, 20};
	int lengthA = sizeof(elemA)/sizeof(elemA[0]);
	int lengthB = sizeof(elemB)/sizeof(elemB[0]);
	cout << "=========�鲢La��Lb�õ��µ����Ա�Lc,������Ԫ�ذ���ֵ�ǵݼ�����========" << endl;
	InsertLinkList(La, elemA, lengthA);
	InsertLinkList(Lb, elemB, lengthB);
	cout << "�������Ա�La��";
	ListTraverse_L(La);
	cout << "�������Ա�Lb��";
	ListTraverse_L(Lb);
	MergeList_L(La, Lb, Lc);
	cout << "�ϲ��󣬱����������Ա�Lc��";
	ListTraverse_L(Lc);
	
	cout << "\n=========ʵ�ּ�������(A-B)��(B-A)========" << endl;
	SLinkList space;
	UnionDifference(space);
	ListTraverse_SL(space);

	cout << "\n==============˫�����������������ʵ��ʵ��================\n" << endl; 
	DisplayDuLinkList();

	cout << "\n==============һԪ����ʽ�ı�ʾ�Լ�����������ʵ��ʵ��================\n" << endl; 
	polynomial Pa, Pb, Pc;
	int m, n;
	cout << "����һԪ����ʽPa��Pb, ��ֱ��������ʽ������";
	cin >> m >> n;
	CreatePolyn(Pa, m);
	CreatePolyn(Pb, n);
	cout << "����һԪ����ʽPa��";
	ListTraverse_P(Pa);
	cout << "����һԪ����ʽPb��";
	ListTraverse_P(Pb);
	AddPolynT(Pa, Pb, Pc);
	cout << "Pa+Pb������µ�һԪ����ʽPc��";
	ListTraverse_P(Pc);
	SubstractPolynT(Pa, Pb, Pc);
	cout << "Pa-Pb������µ�һԪ����ʽPc��";
	ListTraverse_P(Pc);
	MultiplyPolynT(Pa, Pb, Pc);
	cout << "Pa*Pb������µ�һԪ����ʽPc��";
	ListTraverse_P(Pc);
}
