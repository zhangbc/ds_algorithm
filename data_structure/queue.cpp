#include "stdafx.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;


typedef struct
{
	QueuePtr front;   // ��ͷָ��
	QueuePtr rear;    // ��βָ��
}LinkQueue;           // ���е���ʽ�洢�ṹ


typedef struct
{
	QElemType *base;   // ��ʼ���Ķ�̬����洢�ռ�
	int front;         // ͷָ�룬�����в�Ϊ�գ���ָ����ͷԪ��
	int rear;          // βָ�룬�����в�Ϊ�գ���ָ����βԪ�ص���һ��Ԫ��
}SqQueue;              // ѭ������--���е�˳��洢�ṹ


typedef struct
{
	int OccurTime;    // �¼�����ʱ��
	int NType;        // �¼����ͣ�0��ʾ�����¼���1��4��ʾ�ĸ����ڵ��뿪�¼�
}Event, EElemType;    // �¼����ͣ���������EventList������Ԫ������


typedef struct EventNode
{
	EElemType data;
	struct EventNode *next;
}EventNode, *EventList; //��������EventList�Ĵ洢�ṹ


typedef struct 
{
	int ArrivalTime;   // ����ʱ��
	int Duration;      // ������������ʱ��
}QEElemType;           // ���е�����Ԫ������


typedef struct EQNode
{
	QEElemType data;
	struct EQNode *next;
}EQNode, *EQueuePtr;


typedef struct
{
	EQueuePtr front;   // ��ͷָ��
	EQueuePtr rear;    // ��βָ��
}ELinkQueue;           // �¼����е���ʽ�洢�ṹ


// ��ʽ���еĳ�ʼ��
/* ����һ���ն��� */
Status InitQueue_L(LinkQueue &Q)
{
	Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
	if(!Q.front)       // �洢����ʧ��
	{
		exit(OVERFLOW);
	}

	Q.front->next = NULL;
	return OK;
}


// ���ٶ���
/* ���ٶ���Q, Q���ٴ��� */
Status DestroyQueue_L(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear = Q.front ->next;
		free(Q.front);
		Q.front = Q.rear;
	}

	return OK;
}


// ��ն���
/* ��ն���Q */
Status ClearQueue_L(LinkQueue &Q)
{
	Q.front = Q.rear;
	return OK;
}

// �����п�
/* ��QΪ�ն��У��ڷ���TRUE�����򷵻�FALSE */
Status EmptyQueue_L(LinkQueue Q)
{
	return Q.front == Q.rear;
}


// ��ȡ���г���
/* ��ȡ��ʽ����Q��Ԫ�ظ����������еĳ��� */
int QueueLength_L(LinkQueue Q)
{
	if(EmptyQueue_L(Q))
	{
		return 0;
	}

	QNode *p;
	int count = 0;
	p = Q.front->next;
	while(p)
	{
		count++;
		p = p->next;
	}

	return count;
}


// �������Ԫ��
/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue_L(LinkQueue &Q, QElemType e)
{
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	if(!p)     // �洢����ʧ��
	{
		exit(OVERFLOW);
	}

	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}


// ɾ������Ԫ��
/* �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status DeQueue_L(LinkQueue &Q, QElemType &e)
{
	if(EmptyQueue_L(Q))
	{
		return ERROR;
	}

	QNode *p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;

	if(Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
	return OK;
}


// ��ʽ���еı���
Status QueueTraverse_L(LinkQueue Q)
{
	if(EmptyQueue_L(Q))
	{
		cout << "Empty Queue!" << endl;
		return ERROR;
	}

	QNode *p;
	p = Q.front->next;
	while(p)
	{
		cout << p->data << " ";
		p = p->next;
	}

	cout << endl;
	return OK;
}


// ѭ�����еĳ�ʼ��
/* ����һ���ն��� */
Status InitQueue_Sq(SqQueue &Q)
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!Q.base)       // �洢����ʧ��
	{
		exit(OVERFLOW);
	}

	Q.front = Q.rear = 0;
	return OK;
}


// ���ٶ���
/* ���ٶ���Q, Q���ٴ��� */
Status DestroyQueue_Sq(SqQueue &Q)
{
	while(Q.front != Q.rear)
	{
		free(&Q.base[Q.front]);
		Q.front = (Q.front + 1) % MAXQSIZE;
	}

	return OK;
}


// ��ն���
/* ��ն���Q */
Status ClearQueue_Sq(SqQueue &Q)
{
	Q.front = Q.rear = 0;
	return OK;
}

// �����п�
/* ��QΪ�ն��У��ڷ���TRUE�����򷵻�FALSE */
Status EmptyQueue_Sq(SqQueue Q)
{
	return Q.front == Q.rear;
}


// ��������
/* ��QΪ�����У��ڷ���TRUE�����򷵻�FALSE */
Status FullQueue_Sq(SqQueue Q)
{
	return (Q.rear + 1) % MAXQSIZE == Q.front;
}


// ��ȡ���г���
/* ��ȡѭ������Q��Ԫ�ظ����������еĳ��� */
int QueueLength_Sq(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


// �������Ԫ��
/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue_Sq(SqQueue &Q, QElemType e)
{
	if(FullQueue_Sq(Q))  // ����
	{
		cout << "Full Queue!" << endl;
		return ERROR;
	}

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}


// ɾ������Ԫ��
/* �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status DeQueue_Sq(SqQueue &Q, QElemType &e)
{
	if(EmptyQueue_Sq(Q))  // �ӿ�
	{
		return ERROR;
	}

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}


// ���еı���
/* �Ӷ�ͷ����β���ζ�ջ��ÿ��Ԫ�ص��ú���visit()��
   һ������ʧ�ܣ������ʧ�ܡ�*/
Status visitq(QElemType e)
{
	cout << e << " ";
	return OK;
}

Status QueueTraverse_Sq(SqQueue Q, Status(*visitq)(QElemType))
{
	if(EmptyQueue_Sq(Q))
	{
		cout << "Empty Queue!" << endl;
		return ERROR;
	}

	int p;
	p = Q.front;
	while(p != Q.rear)
	{
		visitq(Q.base[p]);
		p = (p + 1) % MAXQSIZE;
	}

	cout << endl;
	return OK;
}


// �㷨3.6~3.7����ɢ�¼�ģ��
EventList ev;                // �¼���
Event en;                    // �¼�
ELinkQueue q[5];              // 4���ͻ�����
QEElemType customer;         // �ͻ���¼
int TotalTime, CustomerNum;  // �ۼƿͻ�����ʱ�䣬�ͻ���

/* ���¼�a�ķ���ʱ�� <��=��> �¼�b�ķ���ʱ�̷ֱ𷵻�-1��0��1�� */
int cmp(Event a, Event b)
{
	int result;
	if(a.OccurTime < b.OccurTime)
	{
		result = -1;
	}
	else if(a.OccurTime == b.OccurTime)
	{
		result = 1;
	}
	else 
	{
		result = 0;
	}

	return result;
}


/* ��ʼ��EventList���� */
Status InitEventList(EventList &L)
{
	L = (EventList)malloc(sizeof(EventNode));
	if(!L)
	{
		exit(OVERFLOW);
	}
	
	L->data.OccurTime = 0;
	L->data.NType = 0;
	L->next = NULL;  // ����һ����ͷ���ĵ�����
	return OK;
}


/* �ж�EventList�����Ƿ�Ϊ�� */
Status EventListEmpty(EventList L)
{
	return L->next == NULL;
}


/* �����µĽ�㲢��ֵ */
Status MakeNode_E(EventNode *pNode, EElemType e)
{
	if(!pNode)
	{
		exit(OVERFLOW);
	}

	pNode->data.NType = e.NType;
	pNode->data.OccurTime = e.OccurTime;
	pNode->next = NULL;
	return OK;
}


/* ����������L�д�����e�����ж�����cmp()ȡֵΪ0��Ԫ�أ���qָʾL�е�һ��ֵΪe�Ľ���λ�ã�������
   TRUE������qָʾ��һ����e�����ж�����cmp()ȡֵ>0��Ԫ�ص�ǰ����λ�ã�������FASLE�� */
Status LocateElem_E(EventList L, EElemType e, int &q, Status(*cmp)(EElemType, EElemType))
{
	EventNode *p;
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
Status OrderInsert(EventList &L, Event e, Status(*cmp)(EElemType, EElemType))
{
	if(e.NType < 0 || e.NType > 4)  // �¼����Ͳ��Ϸ�
	{
		return ERROR;
	}

	EventNode *p, *q;
	int pos;
	q = (EventNode *)malloc(sizeof(EventNode));
	if(!MakeNode_E(q, e))
	{
		return ERROR;
	}
	
	LocateElem_E(L, e, pos, cmp);

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


/* �¼����г�ʼ��������һ���ն��С�*/
Status InitEQueue(ELinkQueue &Q)
{
	Q.front = Q.rear = (EQNode *)malloc(sizeof(EQNode));
	if(!Q.front)       // �洢����ʧ��
	{
		exit(OVERFLOW);
	}

	Q.front->next = NULL;
	return OK;
}


/* �¼������пգ���QΪ�ն��У��ڷ���TRUE�����򷵻�FALSE */
Status EmptyEQueue(ELinkQueue Q)
{
	return Q.front == Q.rear;
}


/* ��ȡ�¼����г��ȣ����¼�����Q��Ԫ�ظ��� */
int EQueueLength(ELinkQueue Q)
{
	if(EmptyEQueue(Q))
	{
		return 0;
	}

	EQNode *p;
	int count = 0;
	p = Q.front->next;
	while(p)
	{
		count++;
		p = p->next;
	}

	return count;
}


/* �����¼�����Ԫ�أ�����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnEQueue(ELinkQueue &Q, QEElemType e)
{
	EQNode *p;
	p = (EQNode *)malloc(sizeof(EQNode));
	if(!p)     // �洢����ʧ��
	{
		exit(OVERFLOW);
	}

	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}


/* ɾ���¼�����Ԫ�أ������в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status DeEQueue(ELinkQueue &Q, QEElemType &e)
{
	if(EmptyEQueue(Q))
	{
		return ERROR;
	}

	EQNode *p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;

	if(Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
	return OK;
}


/* ��������г�����̵Ķ��б��(��0��ʼ)*/
int Minimum(ELinkQueue eq[], int length)
{
	if(length < 1)
	{
		return ERROR; 
	}

	int i, j, min, len;
	min = EQueueLength(eq[0]);
	j = 0;
	for(i = 0; i < length; i++)
	{
		len = EQueueLength(eq[i]);
		if(min > len)
		{
			j = i;
			min = len;
		}
	}

	return j;
}

/* ��ʼ������ */
void OpenForDay()
{
	TotalTime = 0, CustomerNum = 0;  // ��ʼ���ۼ�ʱ��Ϳͻ���Ϊ0
	InitEventList(ev);                    // ��ʼ���¼�����Ϊ�ձ�      
	en.OccurTime = 0;                // �趨��һ���ͻ��ﵽ�¼�
	en.NType = 0;
	OrderInsert(ev, en, cmp);        // �����¼���
	for(int i = 0; i <= 4; i++)      // �ÿն���
	{
		InitEQueue(q[i]);
	}
}


/* ����ͻ������¼���en.NType=0 */
void CustomerArrived(int CloseTime)
{
	Event e;
	++CustomerNum;
	
	/* �����������������������ʱ�估����һ�ͻ��������ʱ������*/
	int durtime = rand() % 30 + 1;  
	int intertime = rand() % 5 + 1;
	int t = en.OccurTime + intertime;    // ��һ���ͻ�����ʱ��
	cout << "������������ʱ��: " << durtime << ", ��һ�ͻ��������ʱ����: " << intertime;
	cout << ", ��һ���ͻ�����ʱ��: " << t << endl; 
	if(t < CloseTime)                // ������δ���ţ������¼���
	{
		e.NType = 0;
		e.OccurTime = t;
		OrderInsert(ev, e, cmp);
	}
	
	int length = sizeof(q)/sizeof(ELinkQueue);
	int i = Minimum(q, length);     // �󳤶���̵Ķ���
	cout << length << "�������Ŷ���̵Ķ��б��Ϊ: " << i + 1 << endl;

	/* �趨��i�����е�һ���뿪�¼��������¼��� */
	QEElemType eq;
	eq.ArrivalTime = en.OccurTime;
	eq.Duration = durtime;
	EnEQueue(q[i], eq);
	if(EQueueLength(q[i]) == 1)
	{	
		e.NType = i;
		e.OccurTime = en.OccurTime + durtime;
		OrderInsert(ev, e, cmp);
	}
}


/* ����ͻ��뿪�¼���en.NType>0�� */
void CustomerDeparture()
{
	Event e;
	int i = en.NType;
	DeEQueue(q[i], customer);  // ɾ����i���е���ͷ�ͻ�
	cout << "��" << i << "���е���ͷ�ͻ��뿪ǰ�Ĵﵽʱ�䣺" << customer.ArrivalTime;
	cout << ", ����ʱ�䣺" << customer.Duration;
	TotalTime += en.OccurTime - customer.ArrivalTime;  // �ۼƿͻ�����ʱ��
	cout << ", ���ۼƿͻ�����ʱ�䣺" << TotalTime << endl;

	if(!EmptyEQueue(q[i]))        // �趨��i���е�һ���뿪�¼��������¼���
	{
		customer = q[i].front->next->data;
		e.NType = i;
		e.OccurTime = en.OccurTime + customer.Duration;
		OrderInsert(ev, e, cmp);
	}
}


/* ����ҵ��ģ�⣬ͳ��һ���ڿͻ������ж�����ƽ��ʱ�䡣*/
void BankSimulation(int CloseTime)
{
	OpenForDay();      // ��ʼ��
	EventNode *p, *q;
	p = ev;
	while(!EventListEmpty(p))
	{
		q = p->next;
		p->next = q->next;
		en = q->data;
		free(q);
		if(en.NType == 0)
		{
			CustomerArrived(CloseTime);     // ����ͻ������¼�
		}
		else
		{
			CustomerDeparture();   // ����ͻ��뿪�¼�
		}
	}

	float durtime = (float)TotalTime / CustomerNum;      // ����ƽ������ʱ��
	cout << "The Average Time is " << durtime << ".\n";
}


// ��ʽ���еĻ�����������ʵ��ʵ��
void DisplayLinkQueue()
{
	LinkQueue LQ;
	QElemType e;
	cout << "��ʼ����ʽ����LQ�С���" << endl;
	InitQueue_L(LQ);

	cout << "��ʽ����LQ�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_L(LQ) << endl;

	cout << "\n��ʽ����LQ����Ԫ�ء���" << endl;
	for(int i = 0; i <= 6; i++)
	{
		e = 'a' + i;
		EnQueue_L(LQ, e);
	}

	cout << "��ʽ����LQ�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_L(LQ) << endl;
	cout << "\n��ʽ����LQ����Ϊ��" << QueueLength_L(LQ) << endl;

	cout << "\n��ʽ����LQ��";
	QueueTraverse_L(LQ);

	DeQueue_L(LQ, e);
	cout << "\n��ʽ����LQɾ��Ԫ�أ�" << e << endl;
	cout << "ɾ����, ������ʽ����LQ��";
	QueueTraverse_L(LQ);

	ClearQueue_L(LQ);
	cout << "\n�����ʽ����LQ..." << endl;
	cout << "��ʽ����LQ�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_L(LQ) << endl;
	
	DestroyQueue_L(LQ);
	cout << "\n������ʽ����LQ..." << endl;
}


// ѭ�����еĻ�����������ʵ��ʵ��
void DisplaySqQueue()
{
	SqQueue Q;
	QElemType e;
	cout << "��ʼ��ѭ������Q�С���" << endl;
	InitQueue_Sq(Q);

	cout << "ѭ������Q�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_Sq(Q) << endl;

	cout << "\nѭ������Q����Ԫ�ء���" << endl;
	for(int i = 0; i <= 8; i++)
	{
		e = 'A' + i;
		EnQueue_Sq(Q, e);
	}

	cout << "ѭ������Q�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_Sq(Q) << endl;
	cout << "ѭ������Q�Ƿ�����? (1Ϊ����,0Ϊδ��): " << FullQueue_Sq(Q) << endl;
	cout << "\nѭ������Q����Ϊ��" << QueueLength_Sq(Q) << endl;

	cout << "\nѭ������Q��";
	QueueTraverse_Sq(Q, visitq);

	DeQueue_Sq(Q, e);
	cout << "\nѭ������Qɾ��Ԫ�أ�" << e << endl;
	DeQueue_Sq(Q, e);
	cout << "\nѭ������Qɾ��Ԫ�أ�" << e << endl;
	cout << "\nɾ����, ѭ������Q����Ϊ��" << QueueLength_Sq(Q) << endl;
	cout << "ɾ����, ����ѭ������Q��";
	QueueTraverse_Sq(Q, visitq);
	
	e = 'Z';
	EnQueue_Sq(Q, e);
	cout << "\nѭ������Q�Ƿ�����? (1Ϊ����,0Ϊδ��): " << FullQueue_Sq(Q) << endl;
	cout << "\nѭ������Q����Ϊ��" << QueueLength_Sq(Q) << endl;

	cout << "\nѭ������Q��";
	QueueTraverse_Sq(Q, visitq);
	
	ClearQueue_Sq(Q);
	cout << "\n���ѭ������Q..." << endl;
	cout << "ѭ������Q�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << EmptyQueue_Sq(Q) << endl;
	
	DestroyQueue_Sq(Q);
	cout << "\n����ѭ������Q..." << endl;
}


void TestQueue()
{
	cout << "==============���еĻ���������������㷨��ʾ================\n" << endl;
	cout << "==============��ʽ���еĻ�����������ʵ��ʵ��================\n" << endl;
	DisplayLinkQueue();
	cout << "\n==============ѭ�����еĻ�����������ʵ��ʵ��================\n" << endl;
	DisplaySqQueue();
	cout << "\n============== ����ҵ��ģ�⣬ͳ��һ���ڿͻ������ж�����ƽ��ʱ��==========\n" << endl;
	BankSimulation(18);
	cout << endl;
}