/* Ԥ���峣�� */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define SIZE 100
#define LIST_INIT_SIZE 100  // ���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10    // ���Ա�洢�ռ�ķ�������
		
#define MAXSIZE 1000         // һ������ʾ����С˳������󳤶Ȼ����������󳤶�
#define MAX_NUM_OF_KEY 10    // �ؼ������������ֵ
#define RADIX 10             // �ؼ��ֻ�������ʱ��ʮ������������
#define MAX_SPACE 10000   

#define STACK_INIT_SIZE 100   // ջ�Ĵ洢�ռ��ʼ������
#define STACKINCREMENT 10     // ջ�Ĵ洢�ռ�ķ�������
#define MAXQSIZE 10          // �����г���


// ��02�� ���Ա�
typedef int ElemType;
typedef char CElemType;
typedef int MazeType;


/* ���Ա��˳��ṹʵ�� */
void TestLinearListSq();

/* ���Ա����ʽ�ṹʵ�� */
void TestLinearLinkList();

/* ���Ա����ʽ�ṹʵ�ּ���Ӧ�� */
void TestLinearLinkList();


// ��03�� ջ�Ͷ���
typedef char SElemType;
typedef double DSElemType;
typedef char QElemType;
/* ջ��˳��ṹʵ�� */
void TestStack();

/* ջ��˳��ṹʵ�� */
void TestQueue();


// ��10�� �ڲ�����
void TestInnerSort();