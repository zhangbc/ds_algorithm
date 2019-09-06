#include "stdafx.h"
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct
{
	SElemType *base;	    // 栈底指针，在栈构造之前和销毁之后都为NULL
	SElemType *top;			// 栈顶指针
	int stacksize;          // 当前已分配的存储空间，以元素为单位
}SqStack;                   // 栈的顺序存储结构


typedef struct
{
	int row;				// 行坐标
	int col;				// 列坐标
}PosType;                   // 通道块在迷宫中“坐标位置”的数据类型


typedef struct
{
	int ord;				 // 通道块在路径上的“序号”
	PosType seat;			 // 通道块在迷宫中的“坐标位置”
	int di;					 // 从此通道块走向下一通道块的“方向”
}MSElemType;                 // 迷宫问题的算法求解的数据元素类型(栈)


typedef struct
{
	MSElemType *base;	    // 栈底指针，在栈构造之前和销毁之后都为NULL
	MSElemType *top;	    // 栈顶指针
	int stacksize;          // 当前已分配的存储空间，以元素为单位
}MSqStack;                  // 迷宫栈的顺序存储结构


typedef struct
{
	DSElemType *base;	    // 栈底指针，在栈构造之前和销毁之后都为NULL
	DSElemType *top;			// 栈顶指针
	int stacksize;          // 当前已分配的存储空间，以元素为单位
}DSqStack;                   // 运算操作数栈的顺序存储结构


// 顺序栈的初始化
/* 构造一个空栈S */
Status InitStack_Sq(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // 存储分配失败
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


// 销毁顺序栈
/* 销毁顺序栈S，S不再存在。*/
Status DestroyStack_Sq(SqStack &S)
{
	S.top = NULL;
	S.stacksize = 0;
	free(S.base);
	return OK;
}


// 顺序栈置空
Status ClearStack_Sq(SqStack &S)
{
	S.top = S.base;
	return OK;
}


// 判断顺序栈是否为空
/* 若栈S为空栈，则返回TRUE，否则返回FALSE。*/
Status StackEmpty_Sq(SqStack S)
{
	return S.top == S.base;
}


// 获取顺序栈的长度
/* 返回S的元素个数，即栈的长度。*/
int StackLength_Sq(SqStack S)
{
	return S.top - S.base;
}


// 获取栈顶元素
/* 若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR。*/
Status GetTop_Sq(SqStack S, SElemType &e)
{
	if(StackEmpty_Sq(S))
	{
		return ERROR;
	}
	
	e = *(S.top - 1);
	return OK;
}


// 进栈
/* 插入元素e为的新的栈顶元素 */
Status Push_Sq(SqStack &S, SElemType e)
{
	if(S.top - S.base >= S.stacksize)  // 栈满，追加存储空间
	{
		S.base = (SElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if(!S.base)  // 存储分配失败
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


// 出栈
/* 若栈不空，则删除S的栈顶元素，用e返回S的栈顶元素，并返回OK，否则返回ERROR。*/
Status Pop_Sq(SqStack &S, SElemType &e)
{
	if(StackEmpty_Sq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


// 栈的遍历
/* 从栈底到栈顶依次对栈中每个元素调用函数visit()，
   一旦调用失败，则操作失败。*/
Status visit(SElemType e)
{
	cout << e << " ";
	return OK;
}

Status StackTraverse_Sq(SqStack S, Status(*visit)(SElemType))
{
	if(S.base == NULL)
	{
		cout << "Destroyed Stack!" << endl;
		return ERROR;
	}

	if(StackEmpty_Sq(S))
	{
		cout << "Empty Stack!" << endl;
		return ERROR;
	}

	SElemType *p;
	p = S.top;
	while(p > S.base)
	{
		p--;
		visit(*p);
	}

	cout << endl;
	return OK;
}


// 算法3.1，数制转换
/* 对于输入的任意一个非负十进制整数，打印输出与其相等的八进制数。
   例如：(1348)_10=(2504)_8*/
Status Conversion()
{
	SqStack S;
	SElemType e;
	InitStack_Sq(S);  // 初始化
	
	int number;
	cout << "请输入一个非负十进制整数：";
	cin >> number;
	if(number <= 0)
	{
		cout << "输入数据不符合要求，请检查!" << endl;
		return ERROR;
	}

	while(number)  // 进栈
	{
		e = number % 8 + '0';
		Push_Sq(S, e);
		number = number / 8;
	}
	
	cout << "转换后的八进制数为：";
	while(!StackEmpty_Sq(S)) // 出栈
	{
		Pop_Sq(S, e);
		cout << e;
	}
	cout << endl;

	return OK;
}


// 括号匹配检查
/* 只考虑[]和()两种括号，检查匹配是否合法或者正确，合法返回TRUE，否则返回FALSE。
   例如：[([][])]是合法的，[(]是不合法的。 */
Status CheckBrackets(SElemType *chr)
{
	SqStack S;
	InitStack_Sq(S);  // 初始化
	
	SElemType e, ch;
	int i = 0;
	ch = chr[0];
	while(ch != '\0')
	{
		if(ch == '[' || ch == '(')
		{
			Push_Sq(S, ch);
		}
		
		if(ch == ']' || ch == ')')
		{	
			GetTop_Sq(S, e);
			if((ch == ']' && e == '[') || (ch == ')' && e == '('))
			{
				Pop_Sq(S, e);
			}
			else
			{
				Push_Sq(S, ch);
			}
		}
		ch = chr[++i];
	}
	
	return S.top == S.base;
}


// 算法3.2，行编辑程序
// 逆序遍历字符栈S
Status VisitLineEdit(SqStack S)
{
	SElemType e;
	SqStack Q;
	InitStack_Sq(Q);  // 初始化，构造空栈
	while(!StackEmpty_Sq(S))
	{
		Pop_Sq(S, e);
		Push_Sq(Q, e);
	}
	
	SElemType *p;
	p = Q.top;
	while(p > Q.base)
	{
		p--;
		cout << *p;
	}
	cout << endl;
	DestroyStack_Sq(Q);
	return OK;
}


/* 利用字符栈S，从终端接收一行并传送至调用过程的数据区。 
   例如：输入：whli##ilr#e(s#*s)
                 outcha@      putchar(*s=#++);
         输出：while(*s)
                 putchar(*s++)*/
void LineEdit(SElemType *chr)
{
	SqStack S;
	InitStack_Sq(S);  // 初始化，构造空栈
	
	SElemType e, ch;
	int i = 0;
	ch = chr[i];       // 从终端接收第一个字符
	while(ch != '\0') 
	{
		while(ch != '\0' && ch != '\n')
		{
			switch(ch)
			{
			case '#':           // 仅当栈非空时退栈
				Pop_Sq(S, e);
				break;
			case '@':           // 重置栈S为空栈
				ClearStack_Sq(S); 
				break;
			default:            // 有效字符进栈，未考虑栈满的情况
				Push_Sq(S, ch);
				break;
			}
			ch = chr[++i];
		}

		// 将从栈底到栈顶的栈内字符传送至调用过程的数据区
		VisitLineEdit(S);
		ClearStack_Sq(S);   // 重置栈S为空栈
		ch = chr[++i];
	}

	DestroyStack_Sq(S);
}


// 算法3.3，迷宫求解
/* 构造迷宫地图(10*10的方阵)为全局变量 */
MazeType MazeMap[10][10] = {
  /* 0  1  2  3  4  5  6  7  8  9 */
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 0
	{0, 1, 1, 0, 1, 1, 1, 0, 1, 0},  // 1
	{0, 1, 1, 0, 1, 1, 1, 0, 1, 0},  // 2
	{0, 1, 1, 1, 1, 0, 0, 1, 1, 0},  // 3
	{0, 1, 0, 0, 0, 1, 1, 1, 1, 0},  // 4
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 0},  // 5
	{0, 1, 0, 1, 1, 1, 0, 1, 1, 0},  // 6
	{0, 1, 0, 0, 0, 1, 0, 0, 1, 0},  // 7
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 0},  // 8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // 9
};


/* 输出迷宫地图(1表示可通过，0表示不能通过) */
void PrintMazeMap()
{
	int row = sizeof(MazeMap) / sizeof(MazeMap[0]);
	int col;
	int i, j;
	cout << "迷宫地图如下所示：\n";
	for(i = 0; i < row; i++)
	{
		cout << "                    ";
		col = sizeof(MazeMap[i]) / sizeof(MazeType);
		for(j = 0; j < col; j++)
		{
			cout << MazeMap[i][j] << "  ";
		}
		cout << endl;
	}
}


/* 初始化: 构造一个空栈S */
Status InitStack_MSq(MSqStack &S)
{
	S.base = (MSElemType *)malloc(STACK_INIT_SIZE * sizeof(MSElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // 存储分配失败
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/* 顺序栈置空 */
Status ClearStack_MSq(MSqStack &S)
{
	S.top = S.base;
	return OK;
}


/* 判断顺序栈是否为空: 若栈S为空栈，则返回TRUE，否则返回FALSE。*/
Status StackEmpty_MSq(MSqStack S)
{
	return S.top == S.base;
}


/* 进栈：插入元素e为的新的栈顶元素 */
Status Push_MSq(MSqStack &S, MSElemType e)
{
	if(S.top - S.base >= S.stacksize)  // 栈满，追加存储空间
	{
		S.base = (MSElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(MSElemType));
		if(!S.base)  // 存储分配失败
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


/* 出栈：若栈不空，则删除S的栈顶元素，用e返回S的栈顶元素，并返回OK，否则返回ERROR。*/
Status Pop_MSq(MSqStack &S, MSElemType &e)
{
	if(StackEmpty_MSq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


/* 判断当前位置是否可以通过(1表示可通过，0表示不能通过) */
Status Pass(PosType pos)
{
	return MazeMap[pos.row][pos.col] == 1;
}


/* 获取当前位置的下一个位置 */
PosType NextPos_MS(PosType curpos, int i)
{
	switch(i)
	{
	case 1:
		curpos.row++;    // 南
		break;
	case 2:
		curpos.col++;    // 西
		break;
	case 3:
		curpos.row--;    // 北
		break;
	case 4:
		curpos.col--;    // 东
		break;
	}

	return curpos;
}


/* 留下能通过的标记*/
void FootPrint(PosType pos, int curstep)
{
	MazeMap[pos.row][pos.col] = curstep;
}


/* 留下不能通过的标记，将走不通的块置为0 */
void MarkPrint(PosType pos)
{
	cout << " (" << pos.row << "," << pos.col << ")走不通.";
	MazeMap[pos.row][pos.col] = 0;  // 将走不通的块置为0
}


/* 比较两个位置a, b是否为同一位置 */
Status cmp_pos(PosType a, PosType b)
{
	return (a.row == b.row) && (a.col == b.col);
}


/* 若迷宫MazeMap中存在从入口start到出口end的通道，则求得一条存放在栈中
   (从栈底到栈顶)，并返回TRUE，否则返回FALSE。 */
MazePath(PosType start, PosType end)
{
	MSqStack S;
	InitStack_MSq(S);
	MSElemType e;
	PosType curpos = start;    // 设置“当前位置”为“入口位置”
	int curstep = 1;       // 搜索第一步
	cout << "\n迷宫探索过程，起点：(" << start.row << "," << start.col << ")";

	do
	{
		if(Pass(curpos))  // 当前位置可以通过，即是未曾走到过的通道块
		{
			FootPrint(curpos, curstep);        // 留下足迹
			cout << " ->(" << curpos.row << "," << curpos.col << ")";
			
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			Push_MSq(S, e);               // 加入到路径
			if(cmp_pos(curpos, end))         // 达到终点(出口)
			{
				cout << " 到达终点：(" << curpos.row << "," << curpos.col << ")\n" << endl;
				return TRUE;
			}

			curpos = NextPos_MS(curpos, 1);    // 下一位置是当前位置的东邻
			curstep++;                      // 搜索下一步
		}
		else              // 当前位置不能通过
		{
			if(!StackEmpty_MSq(S))
			{
				Pop_MSq(S, e);
				while(e.di == 4 && !StackEmpty_MSq(S))  // 留下不能通过的标记，并退回一步
				{
					MarkPrint(e.seat);
					Pop_MSq(S, e);
					curstep--;
					cout << " 倒退到(" << e.seat.row << "," << e.seat.col << ")" << endl;
				}

				if(e.di < 4)  // 换下一个方向探索
				{
					e.di++;
					Push_MSq(S, e);
					curpos = NextPos_MS(e.seat, e.di);      // 设置当前位置是该新方向上的相邻块
				}
			}
		}
	}while(!StackEmpty_MSq(S));
	
	cout << "对不起，找不到出口!" << endl;
	return FALSE;
}

/* 迷宫算法具体实现 */
void DisplayMazeMap()
{
	PrintMazeMap();
	PosType start, end;
	start.row = 1;
	start.col = 1;
	end.row = 8;
	end.col = 8;
	MazePath(start, end);
	PrintMazeMap();
}


// 算法3.4，算术表达式求值
/* 构造一个运算操作数空栈S */
Status InitStack_DSq(DSqStack &S)
{
	S.base = (DSElemType *)malloc(STACK_INIT_SIZE * sizeof(DSElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // 存储分配失败
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/* 判断顺序栈是否为空：若栈S为空栈，则返回TRUE，否则返回FALSE。*/
Status StackEmpty_DSq(DSqStack S)
{
	return S.top == S.base;
}


/* 获取栈顶元素：若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR。*/
Status GetTop_DSq(DSqStack S, DSElemType &e)
{
	if(StackEmpty_DSq(S))
	{
		return ERROR;
	}
	
	e = *(S.top - 1);
	return OK;
}


/* 进栈：插入元素e为的新的栈顶元素 */
Status Push_DSq(DSqStack &S, DSElemType e)
{
	if(S.top - S.base >= S.stacksize)  // 栈满，追加存储空间
	{
		S.base = (DSElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(DSElemType));
		if(!S.base)  // 存储分配失败
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


/* 出栈：若栈不空，则删除S的栈顶元素，用e返回S的栈顶元素，并返回OK，否则返回ERROR。*/
Status Pop_DSq(DSqStack &S, DSElemType &e)
{
	if(StackEmpty_DSq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


/* 栈的遍历：从栈底到栈顶依次对栈中每个元素调用函数visit()，
   一旦调用失败，则操作失败。*/
Status visitDS(DSElemType e)
{
	cout << e << " ";
	return OK;
}

Status StackTraverse_DSq(DSqStack S, Status(*visitDS)(DSElemType))
{
	if(S.base == NULL)
	{
		cout << "Destroyed Stack!" << endl;
		return ERROR;
	}

	if(StackEmpty_DSq(S))
	{
		cout << "Empty Stack!" << endl;
		return ERROR;
	}

	DSElemType *p;
	p = S.top;
	while(p > S.base)
	{
		p--;
		visitDS(*p);
	}

	cout << endl;
	return OK;
}


/* 判断运算符之间的优先关系，
   op为运算符栈的栈顶运算符，exp为输入的运算符，两者比较结果：
   op < exp = -1; op > exp = 0;op > exp = 1。 */
int Precede(SElemType op, SElemType exp)
{
	int cmp_opt;
	switch(op)
	{
	case '+':
	case '-':
		cmp_opt = (exp == '*' || exp == '/' || exp == '(') ? -1 : 1;
		break;
	case '*':
	case '/':
		cmp_opt = exp == '(' ? -1 : 1;
		break;
	case '(':
		if(exp == ')')
		{
			cmp_opt = 0;
		}
		else if(exp == '#')
		{
			cmp_opt = INT_MIN;
		}
		else
		{
			cmp_opt = -1;
		}
		break;
	case ')':
		cmp_opt = exp == '(' ? 1 : INT_MIN;
		break;
	case '#':
		if(exp == '#')
		{
			cmp_opt = 0;
		}
		else if(exp == ')')
		{
			cmp_opt = INT_MIN;
		}
		else
		{
			cmp_opt = -1;
		}
		break;
	default:
		cmp_opt = INT_MIN;
		break;
	}

	return cmp_opt;
}


/* 二元运算，返回运算结果。 */
DSElemType Operate(DSElemType a, SElemType theta, DSElemType b)
{
	DSElemType result;
	switch(theta)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		result = a / b;
		break;
	case '^':
		result = pow(a, b);
		break;
	default:
		cout << "操作符未定义!" << endl;
		break;
	}

	return result;
}

/* 判断是否为运算符 */
Status IsOperator(SElemType exp, SElemType *OP, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(exp == OP[i])
		{
			return TRUE;
		}
	}
	return FALSE;
}


/* 从给定的表达式中取运算操作数 */
DSElemType GetOpnd(SElemType *expr, int &i, SElemType *OP, int length)
{
	char str[] = "";
	DSElemType e;
	int j = 0, opt;
	i--;

	opt = IsOperator(expr[i], OP, length);  // 判定首位符号位
	if(opt)
	{
		if(expr[i] == '-')
		{
			str[j++] = '-';
		}
		i++;
	}

	while(expr[i] != '\0')
	{
		opt = IsOperator(expr[i], OP, length);
		if(opt)
		{
			break;
		}

		if(!opt)
		{
			str[j++] = expr[i];
		}
		i++;
	}

	e = str == NULL ? 0.0 : atof(str);
	return e;
}


/* 算术表达式求值的算符优先算法，
   设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合。
   测试用例：1) input: 1--2# output: 3.000(减负数)
			 2) input: -1-2# output: -3.000(两负数)
			 3) input: -1--2# output: 1.000(负数减负数)
			 4) input: 3.66+4.34# output: 8.000(小数数)(√)
			 5) input: 2*2+4--3^2# output: -1.000(长串+乘方)
			 6) input: 3.66*2+3-4# output: 6.320(四则运算)(√)
			 7) input: 1+3-4*5/2+3.666# output: -2.339(四则运算) 
			 8) input: 3*(7-2)# output: 15.000(四则运算)(√) */
DSElemType EvaluateExpression(SElemType *expr)
{
	SqStack OPTR;
	DSqStack OPND;
	SElemType OP[] = {'+', '-', '*', '/', '^', '(', ')', '{', '}', '[', ']', '#'};     // 运算符集合
	SElemType op, theta, exp;
	DSElemType e, optA, optB; 
	int i = 0, opr, length_op;
	double number;
	op = '#';
	length_op = sizeof(OP)/sizeof(SElemType);
	
	InitStack_Sq(OPTR);   // 初始化运算符栈
	Push_Sq(OPTR, op);
	InitStack_DSq(OPND);  // 初始化运算数栈
	exp = expr[i++];
	GetTop_Sq(OPTR, op);
	while(exp != '#' ||  op != '#')
	{
		if(!IsOperator(exp, OP, length_op)) // 不是运算符则进栈
		{
			number = GetOpnd(expr, i, OP, length_op);
			e = number;
			Push_DSq(OPND, e);
			exp = expr[i++];
		}
		else
		{
			GetTop_Sq(OPTR, op);
			opr = Precede(op, exp);
			switch(opr)
			{
			case -1:   // 栈顶元素优先权低
				Push_Sq(OPTR, exp);
				GetTop_Sq(OPTR, op);
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				break;
			case 0:  // 脱括号并接收下一字符
				Pop_Sq(OPTR, op);
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				break;
			case 1:  // 退栈并将运算结果入栈
				Pop_Sq(OPTR, theta);
				Pop_DSq(OPND, optB);
				Pop_DSq(OPND, optA);
				e = Operate(optA, theta, optB);
				Push_DSq(OPND, e);
				break;
			default:
				cout << "输入的表达式有误!" << endl;
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				Pop_Sq(OPTR, op);
				break;
			}
		}
	}
	
	GetTop_DSq(OPND, e);
	return e;
}


// 顺序栈的基本操作具体实现实例
void DisplaySeqStack()
{
	SqStack S;
	SElemType e;
	cout << "初始化顺序栈S中……" << endl;
	InitStack_Sq(S);

	cout << "顺序栈S是否为空? (1为空,0为非空): " << StackEmpty_Sq(S) << endl;

	cout << "\n顺序栈S插入元素……" << endl;
	for(int i = 0; i <= 6; i++)
	{
		e = 'a' + i;
		Push_Sq(S, e);
	}

	cout << "顺序栈S是否为空? (1为空,0为非空): " << StackEmpty_Sq(S) << endl;
	cout << "\n顺序栈S长度为：" << StackLength_Sq(S) << endl;

	cout << "\n遍历顺序栈S：";
	StackTraverse_Sq(S, visit);

	Pop_Sq(S, e);
	cout << "\n顺序栈S删除元素：" << e << endl;
	cout << "删除后, 遍历顺序栈S：";
	StackTraverse_Sq(S, visit);

	ClearStack_Sq(S);
	cout << "\n清空顺序栈S..." << endl;
	cout << "顺序栈S是否为空? (1为空,0为非空): " << StackEmpty_Sq(S) << endl;
	
	DestroyStack_Sq(S);
	cout << "\n销毁顺序栈S..." << endl;
}


// 测试函数
void TestStack()
{
	cout << "==============栈的基本操作及其相关算法演示================\n" << endl;
	cout << "==============顺序栈的基本操作具体实现实例================\n" << endl;
	DisplaySeqStack();

	cout << "\n==========================数制转换=========================" << endl;
	Conversion();

	cout << "\n=========================括号匹配检查========================" << endl;
	SElemType *chr;
	chr = "[([][])]";
	int flag;
	flag = CheckBrackets(chr);
	cout << "给定括号组" << chr << "是否合法(1为合法，0为非合法)：" << flag << endl;

	cout << "\n===========================行编辑程序===========================" << endl;
	chr = "whli##ilr#e(s#*s)\noutcha@      putchar(*s=#++);";
	cout << "输入的全文为：\n" << chr << endl;
	cout << "实际有效输出为：" << endl;
	LineEdit(chr);

	cout << "\n===========================迷宫求解===========================" << endl;
	DisplayMazeMap();

	cout << "\n===========================算术表达式求值===========================" << endl;
	SElemType *expr;
	DSElemType oper;
	// 1) input: 1--2# output: 3.000(减负数)
	// 2) input: -1-2# output: -3.000(两负数)
	// 3) input: -1--2# output: 1.000(负数减负数)
	// 4) input: 3.66+4.34# output: 8.000(小数)(ok)
	// 5) input: 2*2+4-3^2# output: -1.000(长串+乘方)
	// 6) input: 3.66*2+3-4# output: 6.320(四则运算)(ok)
	// 7) input: 1+3-4*5/2+3.666# output: -2.339(四则运算) 
	// 8) input: 3*(7-2)# output: 15.000(四则运算)(ok)
	expr = "4+2*3-10/5#";
	oper = EvaluateExpression(expr);
	cout << "表达式：" << expr << " 的值为：" << oper << endl;

	cout << endl;
}