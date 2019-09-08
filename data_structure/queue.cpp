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
	QueuePtr front;   // 对头指针
	QueuePtr rear;    // 队尾指针
}LinkQueue;           // 队列的链式存储结构


typedef struct
{
	QElemType *base;   // 初始化的动态分配存储空间
	int front;         // 头指针，若队列不为空，则指向列头元素
	int rear;          // 尾指针，若队列不为空，则指向列尾元素的下一个元素
}SqQueue;              // 循环队列--队列的顺序存储结构


typedef struct
{
	int OccurTime;    // 事件发生时刻
	int NType;        // 事件类型，0表示到达事件，1至4表示四个窗口的离开事件
}Event, EElemType;    // 事件类型，有序链表EventList的数据元素类型


typedef struct EventNode
{
	EElemType data;
	struct EventNode *next;
}EventNode, *EventList; //有序链表EventList的存储结构


typedef struct 
{
	int ArrivalTime;   // 到达时刻
	int Duration;      // 办理事务所需时间
}QEElemType;           // 队列的数据元素类型


typedef struct EQNode
{
	QEElemType data;
	struct EQNode *next;
}EQNode, *EQueuePtr;


typedef struct
{
	EQueuePtr front;   // 对头指针
	EQueuePtr rear;    // 队尾指针
}ELinkQueue;           // 事件队列的链式存储结构


// 链式队列的初始化
/* 构造一个空队列 */
Status InitQueue_L(LinkQueue &Q)
{
	Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
	if(!Q.front)       // 存储分配失败
	{
		exit(OVERFLOW);
	}

	Q.front->next = NULL;
	return OK;
}


// 销毁队列
/* 销毁队列Q, Q不再存在 */
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


// 清空队列
/* 清空队列Q */
Status ClearQueue_L(LinkQueue &Q)
{
	Q.front = Q.rear;
	return OK;
}

// 队列判空
/* 若Q为空队列，在返回TRUE，否则返回FALSE */
Status EmptyQueue_L(LinkQueue Q)
{
	return Q.front == Q.rear;
}


// 获取队列长度
/* 获取链式队列Q的元素个数，即队列的长度 */
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


// 插入队列元素
/* 插入元素e为Q的新的队尾元素 */
Status EnQueue_L(LinkQueue &Q, QElemType e)
{
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	if(!p)     // 存储分配失败
	{
		exit(OVERFLOW);
	}

	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}


// 删除队列元素
/* 若队列不空，则删除Q的对头元素，用e返回其值，并返回OK；否则返回ERROR */
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


// 链式队列的遍历
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


// 循环队列的初始化
/* 构造一个空队列 */
Status InitQueue_Sq(SqQueue &Q)
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!Q.base)       // 存储分配失败
	{
		exit(OVERFLOW);
	}

	Q.front = Q.rear = 0;
	return OK;
}


// 销毁队列
/* 销毁队列Q, Q不再存在 */
Status DestroyQueue_Sq(SqQueue &Q)
{
	while(Q.front != Q.rear)
	{
		free(&Q.base[Q.front]);
		Q.front = (Q.front + 1) % MAXQSIZE;
	}

	return OK;
}


// 清空队列
/* 清空队列Q */
Status ClearQueue_Sq(SqQueue &Q)
{
	Q.front = Q.rear = 0;
	return OK;
}

// 队列判空
/* 若Q为空队列，在返回TRUE，否则返回FALSE */
Status EmptyQueue_Sq(SqQueue Q)
{
	return Q.front == Q.rear;
}


// 队列判满
/* 若Q为满队列，在返回TRUE，否则返回FALSE */
Status FullQueue_Sq(SqQueue Q)
{
	return (Q.rear + 1) % MAXQSIZE == Q.front;
}


// 获取队列长度
/* 获取循环队列Q的元素个数，即队列的长度 */
int QueueLength_Sq(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


// 插入队列元素
/* 插入元素e为Q的新的队尾元素 */
Status EnQueue_Sq(SqQueue &Q, QElemType e)
{
	if(FullQueue_Sq(Q))  // 队满
	{
		cout << "Full Queue!" << endl;
		return ERROR;
	}

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}


// 删除队列元素
/* 若队列不空，则删除Q的对头元素，用e返回其值，并返回OK；否则返回ERROR */
Status DeQueue_Sq(SqQueue &Q, QElemType &e)
{
	if(EmptyQueue_Sq(Q))  // 队空
	{
		return ERROR;
	}

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}


// 队列的遍历
/* 从队头到队尾依次对栈中每个元素调用函数visit()，
   一旦调用失败，则操作失败。*/
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


// 算法3.6~3.7：离散事件模拟
EventList ev;                // 事件表
Event en;                    // 事件
ELinkQueue q[5];              // 4个客户队列
QEElemType customer;         // 客户记录
int TotalTime, CustomerNum;  // 累计客户逗留时间，客户数

/* 依事件a的发生时刻 <、=、> 事件b的发生时刻分别返回-1、0、1。 */
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


/* 初始化EventList链表 */
Status InitEventList(EventList &L)
{
	L = (EventList)malloc(sizeof(EventNode));
	if(!L)
	{
		exit(OVERFLOW);
	}
	
	L->data.OccurTime = 0;
	L->data.NType = 0;
	L->next = NULL;  // 建立一个带头结点的单链表
	return OK;
}


/* 判断EventList链表是否为空 */
Status EventListEmpty(EventList L)
{
	return L->next == NULL;
}


/* 生成新的结点并赋值 */
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


/* 若有序链表L中存在与e满足判定函数cmp()取值为0的元素，则q指示L中第一个值为e的结点的位置，并返回
   TRUE，否则q指示第一个与e满足判定函数cmp()取值>0的元素的前驱的位置，并返回FASLE。 */
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


/* 按照有序判定函数cmp()的约定，将值为e的结点插入到有序链表L的适当位置上。*/
Status OrderInsert(EventList &L, Event e, Status(*cmp)(EElemType, EElemType))
{
	if(e.NType < 0 || e.NType > 4)  // 事件类型不合法
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


/* 事件队列初始化：构造一个空队列。*/
Status InitEQueue(ELinkQueue &Q)
{
	Q.front = Q.rear = (EQNode *)malloc(sizeof(EQNode));
	if(!Q.front)       // 存储分配失败
	{
		exit(OVERFLOW);
	}

	Q.front->next = NULL;
	return OK;
}


/* 事件队列判空：若Q为空队列，在返回TRUE，否则返回FALSE */
Status EmptyEQueue(ELinkQueue Q)
{
	return Q.front == Q.rear;
}


/* 获取事件队列长度，即事件队列Q的元素个数 */
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


/* 插入事件队列元素：插入元素e为Q的新的队尾元素 */
Status EnEQueue(ELinkQueue &Q, QEElemType e)
{
	EQNode *p;
	p = (EQNode *)malloc(sizeof(EQNode));
	if(!p)     // 存储分配失败
	{
		exit(OVERFLOW);
	}

	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}


/* 删除事件队列元素：若队列不空，则删除Q的对头元素，用e返回其值，并返回OK；否则返回ERROR */
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


/* 求队列组中长度最短的队列编号(从0开始)*/
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

/* 初始化操作 */
void OpenForDay()
{
	TotalTime = 0, CustomerNum = 0;  // 初始化累计时间和客户数为0
	InitEventList(ev);                    // 初始化事件链表为空表      
	en.OccurTime = 0;                // 设定第一个客户达到事件
	en.NType = 0;
	OrderInsert(ev, en, cmp);        // 插入事件表
	for(int i = 0; i <= 4; i++)      // 置空队列
	{
		InitEQueue(q[i]);
	}
}


/* 处理客户到达事件，en.NType=0 */
void CustomerArrived(int CloseTime)
{
	Event e;
	++CustomerNum;
	
	/* 生成随机数：办理事务所需时间及其下一客户将到达的时间间隔。*/
	int durtime = rand() % 30 + 1;  
	int intertime = rand() % 5 + 1;
	int t = en.OccurTime + intertime;    // 下一个客户到达时刻
	cout << "办理事务所需时间: " << durtime << ", 下一客户将到达的时间间隔: " << intertime;
	cout << ", 下一个客户到达时刻: " << t << endl; 
	if(t < CloseTime)                // 银行尚未关门，插入事件表
	{
		e.NType = 0;
		e.OccurTime = t;
		OrderInsert(ev, e, cmp);
	}
	
	int length = sizeof(q)/sizeof(ELinkQueue);
	int i = Minimum(q, length);     // 求长度最短的队列
	cout << length << "个窗口排队最短的队列编号为: " << i + 1 << endl;

	/* 设定第i个队列的一个离开事件并插入事件表 */
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


/* 处理客户离开事件，en.NType>0。 */
void CustomerDeparture()
{
	Event e;
	int i = en.NType;
	DeEQueue(q[i], customer);  // 删除第i队列的排头客户
	cout << "第" << i << "队列的排头客户离开前的达到时间：" << customer.ArrivalTime;
	cout << ", 逗留时间：" << customer.Duration;
	TotalTime += en.OccurTime - customer.ArrivalTime;  // 累计客户逗留时间
	cout << ", 总累计客户逗留时间：" << TotalTime << endl;

	if(!EmptyEQueue(q[i]))        // 设定第i队列的一个离开事件并插入事件表
	{
		customer = q[i].front->next->data;
		e.NType = i;
		e.OccurTime = en.OccurTime + customer.Duration;
		OrderInsert(ev, e, cmp);
	}
}


/* 银行业务模拟，统计一天内客户在银行逗留的平均时间。*/
void BankSimulation(int CloseTime)
{
	OpenForDay();      // 初始化
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
			CustomerArrived(CloseTime);     // 处理客户到达事件
		}
		else
		{
			CustomerDeparture();   // 处理客户离开事件
		}
	}

	float durtime = (float)TotalTime / CustomerNum;      // 计算平均逗留时间
	cout << "The Average Time is " << durtime << ".\n";
}


// 链式队列的基本操作具体实现实例
void DisplayLinkQueue()
{
	LinkQueue LQ;
	QElemType e;
	cout << "初始化链式队列LQ中……" << endl;
	InitQueue_L(LQ);

	cout << "链式队列LQ是否为空? (1为空,0为非空): " << EmptyQueue_L(LQ) << endl;

	cout << "\n链式队列LQ插入元素……" << endl;
	for(int i = 0; i <= 6; i++)
	{
		e = 'a' + i;
		EnQueue_L(LQ, e);
	}

	cout << "链式队列LQ是否为空? (1为空,0为非空): " << EmptyQueue_L(LQ) << endl;
	cout << "\n链式队列LQ长度为：" << QueueLength_L(LQ) << endl;

	cout << "\n链式队列LQ：";
	QueueTraverse_L(LQ);

	DeQueue_L(LQ, e);
	cout << "\n链式队列LQ删除元素：" << e << endl;
	cout << "删除后, 遍历链式队列LQ：";
	QueueTraverse_L(LQ);

	ClearQueue_L(LQ);
	cout << "\n清空链式队列LQ..." << endl;
	cout << "链式队列LQ是否为空? (1为空,0为非空): " << EmptyQueue_L(LQ) << endl;
	
	DestroyQueue_L(LQ);
	cout << "\n销毁链式队列LQ..." << endl;
}


// 循环队列的基本操作具体实现实例
void DisplaySqQueue()
{
	SqQueue Q;
	QElemType e;
	cout << "初始化循环队列Q中……" << endl;
	InitQueue_Sq(Q);

	cout << "循环队列Q是否为空? (1为空,0为非空): " << EmptyQueue_Sq(Q) << endl;

	cout << "\n循环队列Q插入元素……" << endl;
	for(int i = 0; i <= 8; i++)
	{
		e = 'A' + i;
		EnQueue_Sq(Q, e);
	}

	cout << "循环队列Q是否为空? (1为空,0为非空): " << EmptyQueue_Sq(Q) << endl;
	cout << "循环队列Q是否已满? (1为已满,0为未满): " << FullQueue_Sq(Q) << endl;
	cout << "\n循环队列Q长度为：" << QueueLength_Sq(Q) << endl;

	cout << "\n循环队列Q：";
	QueueTraverse_Sq(Q, visitq);

	DeQueue_Sq(Q, e);
	cout << "\n循环队列Q删除元素：" << e << endl;
	DeQueue_Sq(Q, e);
	cout << "\n循环队列Q删除元素：" << e << endl;
	cout << "\n删除后, 循环队列Q长度为：" << QueueLength_Sq(Q) << endl;
	cout << "删除后, 遍历循环队列Q：";
	QueueTraverse_Sq(Q, visitq);
	
	e = 'Z';
	EnQueue_Sq(Q, e);
	cout << "\n循环队列Q是否已满? (1为已满,0为未满): " << FullQueue_Sq(Q) << endl;
	cout << "\n循环队列Q长度为：" << QueueLength_Sq(Q) << endl;

	cout << "\n循环队列Q：";
	QueueTraverse_Sq(Q, visitq);
	
	ClearQueue_Sq(Q);
	cout << "\n清空循环队列Q..." << endl;
	cout << "循环队列Q是否为空? (1为空,0为非空): " << EmptyQueue_Sq(Q) << endl;
	
	DestroyQueue_Sq(Q);
	cout << "\n销毁循环队列Q..." << endl;
}


void TestQueue()
{
	cout << "==============队列的基本操作及其相关算法演示================\n" << endl;
	cout << "==============链式队列的基本操作具体实现实例================\n" << endl;
	DisplayLinkQueue();
	cout << "\n==============循环队列的基本操作具体实现实例================\n" << endl;
	DisplaySqQueue();
	cout << "\n============== 银行业务模拟，统计一天内客户在银行逗留的平均时间==========\n" << endl;
	BankSimulation(18);
	cout << endl;
}