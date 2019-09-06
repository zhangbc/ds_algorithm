#include "stdafx.h"
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct
{
	SElemType *base;	    // ջ��ָ�룬��ջ����֮ǰ������֮��ΪNULL
	SElemType *top;			// ջ��ָ��
	int stacksize;          // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;                   // ջ��˳��洢�ṹ


typedef struct
{
	int row;				// ������
	int col;				// ������
}PosType;                   // ͨ�������Թ��С�����λ�á�����������


typedef struct
{
	int ord;				 // ͨ������·���ϵġ���š�
	PosType seat;			 // ͨ�������Թ��еġ�����λ�á�
	int di;					 // �Ӵ�ͨ����������һͨ����ġ�����
}MSElemType;                 // �Թ�������㷨��������Ԫ������(ջ)


typedef struct
{
	MSElemType *base;	    // ջ��ָ�룬��ջ����֮ǰ������֮��ΪNULL
	MSElemType *top;	    // ջ��ָ��
	int stacksize;          // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}MSqStack;                  // �Թ�ջ��˳��洢�ṹ


typedef struct
{
	DSElemType *base;	    // ջ��ָ�룬��ջ����֮ǰ������֮��ΪNULL
	DSElemType *top;			// ջ��ָ��
	int stacksize;          // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}DSqStack;                   // ���������ջ��˳��洢�ṹ


// ˳��ջ�ĳ�ʼ��
/* ����һ����ջS */
Status InitStack_Sq(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // �洢����ʧ��
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


// ����˳��ջ
/* ����˳��ջS��S���ٴ��ڡ�*/
Status DestroyStack_Sq(SqStack &S)
{
	S.top = NULL;
	S.stacksize = 0;
	free(S.base);
	return OK;
}


// ˳��ջ�ÿ�
Status ClearStack_Sq(SqStack &S)
{
	S.top = S.base;
	return OK;
}


// �ж�˳��ջ�Ƿ�Ϊ��
/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE��*/
Status StackEmpty_Sq(SqStack S)
{
	return S.top == S.base;
}


// ��ȡ˳��ջ�ĳ���
/* ����S��Ԫ�ظ�������ջ�ĳ��ȡ�*/
int StackLength_Sq(SqStack S)
{
	return S.top - S.base;
}


// ��ȡջ��Ԫ��
/* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR��*/
Status GetTop_Sq(SqStack S, SElemType &e)
{
	if(StackEmpty_Sq(S))
	{
		return ERROR;
	}
	
	e = *(S.top - 1);
	return OK;
}


// ��ջ
/* ����Ԫ��eΪ���µ�ջ��Ԫ�� */
Status Push_Sq(SqStack &S, SElemType e)
{
	if(S.top - S.base >= S.stacksize)  // ջ����׷�Ӵ洢�ռ�
	{
		S.base = (SElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if(!S.base)  // �洢����ʧ��
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


// ��ջ
/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR��*/
Status Pop_Sq(SqStack &S, SElemType &e)
{
	if(StackEmpty_Sq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


// ջ�ı���
/* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()��
   һ������ʧ�ܣ������ʧ�ܡ�*/
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


// �㷨3.1������ת��
/* �������������һ���Ǹ�ʮ������������ӡ���������ȵİ˽�������
   ���磺(1348)_10=(2504)_8*/
Status Conversion()
{
	SqStack S;
	SElemType e;
	InitStack_Sq(S);  // ��ʼ��
	
	int number;
	cout << "������һ���Ǹ�ʮ����������";
	cin >> number;
	if(number <= 0)
	{
		cout << "�������ݲ�����Ҫ������!" << endl;
		return ERROR;
	}

	while(number)  // ��ջ
	{
		e = number % 8 + '0';
		Push_Sq(S, e);
		number = number / 8;
	}
	
	cout << "ת����İ˽�����Ϊ��";
	while(!StackEmpty_Sq(S)) // ��ջ
	{
		Pop_Sq(S, e);
		cout << e;
	}
	cout << endl;

	return OK;
}


// ����ƥ����
/* ֻ����[]��()�������ţ����ƥ���Ƿ�Ϸ�������ȷ���Ϸ�����TRUE�����򷵻�FALSE��
   ���磺[([][])]�ǺϷ��ģ�[(]�ǲ��Ϸ��ġ� */
Status CheckBrackets(SElemType *chr)
{
	SqStack S;
	InitStack_Sq(S);  // ��ʼ��
	
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


// �㷨3.2���б༭����
// ��������ַ�ջS
Status VisitLineEdit(SqStack S)
{
	SElemType e;
	SqStack Q;
	InitStack_Sq(Q);  // ��ʼ���������ջ
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


/* �����ַ�ջS�����ն˽���һ�в����������ù��̵��������� 
   ���磺���룺whli##ilr#e(s#*s)
                 outcha@      putchar(*s=#++);
         �����while(*s)
                 putchar(*s++)*/
void LineEdit(SElemType *chr)
{
	SqStack S;
	InitStack_Sq(S);  // ��ʼ���������ջ
	
	SElemType e, ch;
	int i = 0;
	ch = chr[i];       // ���ն˽��յ�һ���ַ�
	while(ch != '\0') 
	{
		while(ch != '\0' && ch != '\n')
		{
			switch(ch)
			{
			case '#':           // ����ջ�ǿ�ʱ��ջ
				Pop_Sq(S, e);
				break;
			case '@':           // ����ջSΪ��ջ
				ClearStack_Sq(S); 
				break;
			default:            // ��Ч�ַ���ջ��δ����ջ�������
				Push_Sq(S, ch);
				break;
			}
			ch = chr[++i];
		}

		// ����ջ�׵�ջ����ջ���ַ����������ù��̵�������
		VisitLineEdit(S);
		ClearStack_Sq(S);   // ����ջSΪ��ջ
		ch = chr[++i];
	}

	DestroyStack_Sq(S);
}


// �㷨3.3���Թ����
/* �����Թ���ͼ(10*10�ķ���)Ϊȫ�ֱ��� */
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


/* ����Թ���ͼ(1��ʾ��ͨ����0��ʾ����ͨ��) */
void PrintMazeMap()
{
	int row = sizeof(MazeMap) / sizeof(MazeMap[0]);
	int col;
	int i, j;
	cout << "�Թ���ͼ������ʾ��\n";
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


/* ��ʼ��: ����һ����ջS */
Status InitStack_MSq(MSqStack &S)
{
	S.base = (MSElemType *)malloc(STACK_INIT_SIZE * sizeof(MSElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // �洢����ʧ��
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/* ˳��ջ�ÿ� */
Status ClearStack_MSq(MSqStack &S)
{
	S.top = S.base;
	return OK;
}


/* �ж�˳��ջ�Ƿ�Ϊ��: ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE��*/
Status StackEmpty_MSq(MSqStack S)
{
	return S.top == S.base;
}


/* ��ջ������Ԫ��eΪ���µ�ջ��Ԫ�� */
Status Push_MSq(MSqStack &S, MSElemType e)
{
	if(S.top - S.base >= S.stacksize)  // ջ����׷�Ӵ洢�ռ�
	{
		S.base = (MSElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(MSElemType));
		if(!S.base)  // �洢����ʧ��
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


/* ��ջ����ջ���գ���ɾ��S��ջ��Ԫ�أ���e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR��*/
Status Pop_MSq(MSqStack &S, MSElemType &e)
{
	if(StackEmpty_MSq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


/* �жϵ�ǰλ���Ƿ����ͨ��(1��ʾ��ͨ����0��ʾ����ͨ��) */
Status Pass(PosType pos)
{
	return MazeMap[pos.row][pos.col] == 1;
}


/* ��ȡ��ǰλ�õ���һ��λ�� */
PosType NextPos_MS(PosType curpos, int i)
{
	switch(i)
	{
	case 1:
		curpos.row++;    // ��
		break;
	case 2:
		curpos.col++;    // ��
		break;
	case 3:
		curpos.row--;    // ��
		break;
	case 4:
		curpos.col--;    // ��
		break;
	}

	return curpos;
}


/* ������ͨ���ı��*/
void FootPrint(PosType pos, int curstep)
{
	MazeMap[pos.row][pos.col] = curstep;
}


/* ���²���ͨ���ı�ǣ����߲�ͨ�Ŀ���Ϊ0 */
void MarkPrint(PosType pos)
{
	cout << " (" << pos.row << "," << pos.col << ")�߲�ͨ.";
	MazeMap[pos.row][pos.col] = 0;  // ���߲�ͨ�Ŀ���Ϊ0
}


/* �Ƚ�����λ��a, b�Ƿ�Ϊͬһλ�� */
Status cmp_pos(PosType a, PosType b)
{
	return (a.row == b.row) && (a.col == b.col);
}


/* ���Թ�MazeMap�д��ڴ����start������end��ͨ���������һ�������ջ��
   (��ջ�׵�ջ��)��������TRUE�����򷵻�FALSE�� */
MazePath(PosType start, PosType end)
{
	MSqStack S;
	InitStack_MSq(S);
	MSElemType e;
	PosType curpos = start;    // ���á���ǰλ�á�Ϊ�����λ�á�
	int curstep = 1;       // ������һ��
	cout << "\n�Թ�̽�����̣���㣺(" << start.row << "," << start.col << ")";

	do
	{
		if(Pass(curpos))  // ��ǰλ�ÿ���ͨ��������δ���ߵ�����ͨ����
		{
			FootPrint(curpos, curstep);        // �����㼣
			cout << " ->(" << curpos.row << "," << curpos.col << ")";
			
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			Push_MSq(S, e);               // ���뵽·��
			if(cmp_pos(curpos, end))         // �ﵽ�յ�(����)
			{
				cout << " �����յ㣺(" << curpos.row << "," << curpos.col << ")\n" << endl;
				return TRUE;
			}

			curpos = NextPos_MS(curpos, 1);    // ��һλ���ǵ�ǰλ�õĶ���
			curstep++;                      // ������һ��
		}
		else              // ��ǰλ�ò���ͨ��
		{
			if(!StackEmpty_MSq(S))
			{
				Pop_MSq(S, e);
				while(e.di == 4 && !StackEmpty_MSq(S))  // ���²���ͨ���ı�ǣ����˻�һ��
				{
					MarkPrint(e.seat);
					Pop_MSq(S, e);
					curstep--;
					cout << " ���˵�(" << e.seat.row << "," << e.seat.col << ")" << endl;
				}

				if(e.di < 4)  // ����һ������̽��
				{
					e.di++;
					Push_MSq(S, e);
					curpos = NextPos_MS(e.seat, e.di);      // ���õ�ǰλ���Ǹ��·����ϵ����ڿ�
				}
			}
		}
	}while(!StackEmpty_MSq(S));
	
	cout << "�Բ����Ҳ�������!" << endl;
	return FALSE;
}

/* �Թ��㷨����ʵ�� */
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


// �㷨3.4���������ʽ��ֵ
/* ����һ�������������ջS */
Status InitStack_DSq(DSqStack &S)
{
	S.base = (DSElemType *)malloc(STACK_INIT_SIZE * sizeof(DSElemType));
	if(!S.base)
	{
		exit(OVERFLOW);  // �洢����ʧ��
	}

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/* �ж�˳��ջ�Ƿ�Ϊ�գ���ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE��*/
Status StackEmpty_DSq(DSqStack S)
{
	return S.top == S.base;
}


/* ��ȡջ��Ԫ�أ���ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR��*/
Status GetTop_DSq(DSqStack S, DSElemType &e)
{
	if(StackEmpty_DSq(S))
	{
		return ERROR;
	}
	
	e = *(S.top - 1);
	return OK;
}


/* ��ջ������Ԫ��eΪ���µ�ջ��Ԫ�� */
Status Push_DSq(DSqStack &S, DSElemType e)
{
	if(S.top - S.base >= S.stacksize)  // ջ����׷�Ӵ洢�ռ�
	{
		S.base = (DSElemType *)realloc(S.base, 
			(S.stacksize + STACKINCREMENT) * sizeof(DSElemType));
		if(!S.base)  // �洢����ʧ��
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top++ = e;
	return OK;
}


/* ��ջ����ջ���գ���ɾ��S��ջ��Ԫ�أ���e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR��*/
Status Pop_DSq(DSqStack &S, DSElemType &e)
{
	if(StackEmpty_DSq(S))
	{
		return ERROR;
	}
	
	e = * --S.top;
	return OK;
}


/* ջ�ı�������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()��
   һ������ʧ�ܣ������ʧ�ܡ�*/
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


/* �ж������֮������ȹ�ϵ��
   opΪ�����ջ��ջ���������expΪ���������������߱ȽϽ����
   op < exp = -1; op > exp = 0;op > exp = 1�� */
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


/* ��Ԫ���㣬������������ */
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
		cout << "������δ����!" << endl;
		break;
	}

	return result;
}

/* �ж��Ƿ�Ϊ����� */
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


/* �Ӹ����ı��ʽ��ȡ��������� */
DSElemType GetOpnd(SElemType *expr, int &i, SElemType *OP, int length)
{
	char str[] = "";
	DSElemType e;
	int j = 0, opt;
	i--;

	opt = IsOperator(expr[i], OP, length);  // �ж���λ����λ
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


/* �������ʽ��ֵ����������㷨��
   ��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ��������ϡ�
   ����������1) input: 1--2# output: 3.000(������)
			 2) input: -1-2# output: -3.000(������)
			 3) input: -1--2# output: 1.000(����������)
			 4) input: 3.66+4.34# output: 8.000(С����)(��)
			 5) input: 2*2+4--3^2# output: -1.000(����+�˷�)
			 6) input: 3.66*2+3-4# output: 6.320(��������)(��)
			 7) input: 1+3-4*5/2+3.666# output: -2.339(��������) 
			 8) input: 3*(7-2)# output: 15.000(��������)(��) */
DSElemType EvaluateExpression(SElemType *expr)
{
	SqStack OPTR;
	DSqStack OPND;
	SElemType OP[] = {'+', '-', '*', '/', '^', '(', ')', '{', '}', '[', ']', '#'};     // ���������
	SElemType op, theta, exp;
	DSElemType e, optA, optB; 
	int i = 0, opr, length_op;
	double number;
	op = '#';
	length_op = sizeof(OP)/sizeof(SElemType);
	
	InitStack_Sq(OPTR);   // ��ʼ�������ջ
	Push_Sq(OPTR, op);
	InitStack_DSq(OPND);  // ��ʼ��������ջ
	exp = expr[i++];
	GetTop_Sq(OPTR, op);
	while(exp != '#' ||  op != '#')
	{
		if(!IsOperator(exp, OP, length_op)) // ������������ջ
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
			case -1:   // ջ��Ԫ������Ȩ��
				Push_Sq(OPTR, exp);
				GetTop_Sq(OPTR, op);
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				break;
			case 0:  // �����Ų�������һ�ַ�
				Pop_Sq(OPTR, op);
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				break;
			case 1:  // ��ջ������������ջ
				Pop_Sq(OPTR, theta);
				Pop_DSq(OPND, optB);
				Pop_DSq(OPND, optA);
				e = Operate(optA, theta, optB);
				Push_DSq(OPND, e);
				break;
			default:
				cout << "����ı��ʽ����!" << endl;
				exp = expr[i] == '\0' ? expr[i - 1] : expr[i++];
				Pop_Sq(OPTR, op);
				break;
			}
		}
	}
	
	GetTop_DSq(OPND, e);
	return e;
}


// ˳��ջ�Ļ�����������ʵ��ʵ��
void DisplaySeqStack()
{
	SqStack S;
	SElemType e;
	cout << "��ʼ��˳��ջS�С���" << endl;
	InitStack_Sq(S);

	cout << "˳��ջS�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << StackEmpty_Sq(S) << endl;

	cout << "\n˳��ջS����Ԫ�ء���" << endl;
	for(int i = 0; i <= 6; i++)
	{
		e = 'a' + i;
		Push_Sq(S, e);
	}

	cout << "˳��ջS�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << StackEmpty_Sq(S) << endl;
	cout << "\n˳��ջS����Ϊ��" << StackLength_Sq(S) << endl;

	cout << "\n����˳��ջS��";
	StackTraverse_Sq(S, visit);

	Pop_Sq(S, e);
	cout << "\n˳��ջSɾ��Ԫ�أ�" << e << endl;
	cout << "ɾ����, ����˳��ջS��";
	StackTraverse_Sq(S, visit);

	ClearStack_Sq(S);
	cout << "\n���˳��ջS..." << endl;
	cout << "˳��ջS�Ƿ�Ϊ��? (1Ϊ��,0Ϊ�ǿ�): " << StackEmpty_Sq(S) << endl;
	
	DestroyStack_Sq(S);
	cout << "\n����˳��ջS..." << endl;
}


// ���Ժ���
void TestStack()
{
	cout << "==============ջ�Ļ���������������㷨��ʾ================\n" << endl;
	cout << "==============˳��ջ�Ļ�����������ʵ��ʵ��================\n" << endl;
	DisplaySeqStack();

	cout << "\n==========================����ת��=========================" << endl;
	Conversion();

	cout << "\n=========================����ƥ����========================" << endl;
	SElemType *chr;
	chr = "[([][])]";
	int flag;
	flag = CheckBrackets(chr);
	cout << "����������" << chr << "�Ƿ�Ϸ�(1Ϊ�Ϸ���0Ϊ�ǺϷ�)��" << flag << endl;

	cout << "\n===========================�б༭����===========================" << endl;
	chr = "whli##ilr#e(s#*s)\noutcha@      putchar(*s=#++);";
	cout << "�����ȫ��Ϊ��\n" << chr << endl;
	cout << "ʵ����Ч���Ϊ��" << endl;
	LineEdit(chr);

	cout << "\n===========================�Թ����===========================" << endl;
	DisplayMazeMap();

	cout << "\n===========================�������ʽ��ֵ===========================" << endl;
	SElemType *expr;
	DSElemType oper;
	// 1) input: 1--2# output: 3.000(������)
	// 2) input: -1-2# output: -3.000(������)
	// 3) input: -1--2# output: 1.000(����������)
	// 4) input: 3.66+4.34# output: 8.000(С��)(ok)
	// 5) input: 2*2+4-3^2# output: -1.000(����+�˷�)
	// 6) input: 3.66*2+3-4# output: 6.320(��������)(ok)
	// 7) input: 1+3-4*5/2+3.666# output: -2.339(��������) 
	// 8) input: 3*(7-2)# output: 15.000(��������)(ok)
	expr = "4+2*3-10/5#";
	oper = EvaluateExpression(expr);
	cout << "���ʽ��" << expr << " ��ֵΪ��" << oper << endl;

	cout << endl;
}