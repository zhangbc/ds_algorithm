// 预定义常量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define SIZE 100
#define LIST_INIT_SIZE 100  // 线性表存储空间的初始分配量
#define LISTINCREMENT  10   // 线性表存储空间的分配增量
		

#define MAXSIZE 1000         // 一个用作示例的小顺序表的最大长度或者链表的最大长度
#define MAX_NUM_OF_KEY 10    // 关键字项数的最大值
#define RADIX 10             // 关键字基数，此时是十进制整数基数
#define MAX_SPACE  10000   


// 第02章 线性表
typedef int ElemType;
typedef char C_ElemType;

/* 线性表的顺序结构实现 */
void TestLinearListSq();

/* 线性表的链式结构实现 */
void TestLinearLinkList();

/* 线性表的链式结构实现及其应用 */
void TestLinearLinkList();

// 第10章 内部排序
void TestInnerSort();