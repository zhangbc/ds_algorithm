#include "stdafx.h"
#include "math.h"
#include "stdlib.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct 
{
	unsigned char data[MAXSTRLEN];           // 串的元素
	int length;                              // 串的长度   
}SString;                                    // 串的定长顺序存储结构


typedef struct
{
	char *ch;     // 若是非空串，则按照串长分配存储区，否则ch为NULL
	int length;   // 串的长度
}HString;         // 串的堆分配存储结构



typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;


typedef struct
{
	Chunk *head, *tail;   // 串的头和尾指针
	int curlen;           // c串的当前长度
}LString;


// 定长顺序存储表示：求串长StrLength(S)
/* 返回S的元素个数，即串的长度。*/
int StrLength_Sq(SString S)
{
	return S.length;
}


// 定长顺序存储表示：比较大小StrCompare(S,T)
/* 若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0。*/
int StrCompare_Sq(SString S, SString T)
{
	for(int i = 0; i < S.length && i < T.length; i++)
	{	
		if(S.data[i] != T.data[i])
		{
			return S.data[i] - T.data[i];
		}
	}

	return S.length - T.length;
}


// 定长顺序串的遍历输出
Status StrTraverse_Sq(SString S)
{
	int len = S.length;
	cout << "长度为：" << len << ", 遍历：";
	for(int i = 0; i < len; i++)
	{
		cout << S.data[i];
	}
	cout << endl;

	return OK;
}


// 定长顺序存储表示：串复制StrCopying(&T, S, pos, len)
/* 返回由S的前len个组成的新子串，
   若未截断，在返回TRUE，否则返回FALSE。
   其中：0<len<=S.length且len<=T.length+pos，T.length<pos<=MAXSTRLEN。*/
Status StrCopying(SString &T, SString S, int pos, int len)
{
	Status uncat;
	int length, j = 0;
	/* 复制中T的起始位置已被占用或者T长度已最大或者复制长度小于1，不合法。*/
	if(pos < T.length || pos > MAXSTRLEN || len < 1 || T.length == MAXSTRLEN)   
	{
		return ERROR;
	}

	if(len > S.length)  // 长度非法，采用S[0]
	{
		len = S.length;
	}

	if(pos + len <= MAXSTRLEN)
	{
		length = len;
		uncat = TRUE;
	}
	else
	{
		length = MAXSTRLEN - (pos + len);
		uncat = FALSE;
	}
	
	for(int i = pos - 1; i < pos + length; i++)
	{
		T.data[i] = S.data[j++];
	}

	T.length += len;
	return uncat;
}


// 算法4.2，定长顺序存储表示：串联接Contcat(&T, S1, S2)
/* 用T返回由S1和S2联接而成的新串，若未截断，在返回TRUE，否则返回FALSE。*/
Status Concat_Sq(SString &T, SString S1, SString S2)
{
	Status uncat;
	T.length = 0;
	if(S1.length + S2.length <= MAXSTRLEN)  // 未截断
	{
		StrCopying(T, S1, 1, S1.length);
		StrCopying(T, S2, T.length+1, S2.length);
		uncat = TRUE;
	}
	else if(S1.length < MAXSTRLEN)     // 截断(取S2部分)
	{
		StrCopying(T, S1, 1, S1.length);
		StrCopying(T, S1, T.length + 1, MAXSTRLEN - T.length);
		uncat = FALSE;
	}
	else                           // 截断(仅取S1)
	{
		StrCopying(T, S1, 1, S1.length);
		uncat = FALSE;
	}

	return uncat;
}


// 算法4.3，定长顺序存储表示：求子串SubString(&Sub, S, pos, len)
/* 用Sub返回S的第pos个字符起长度为len的子串。
   其中，1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1。*/
Status SubString_Sq(SString &Sub, SString S, int pos, int len)
{
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
	{
		return ERROR;
	}

	for(int i = 0; i <= len; i++)
	{
		Sub.data[i] = S.data[(pos++)-1];
	}
	Sub.length = len;
	
	return OK;
}


// 算法4.1，定位函数Index(S, T, pos)
/* T为非空串，若主串S中第pos个字符之后存在与T相等的子串，
   则返回第一个这样的子串在S中的位置，否则返回0。*/
int Index_Sq(SString S, SString T, int pos)
{
	if(pos <= 0)
	{
		return 0;
	}
	
	SString sub;
	int n, m, i;
	n = StrLength_Sq(S);
	m = StrLength_Sq(T);
	i = pos;
	while(i < n - m + 1)
	{
		SubString_Sq(sub, S, i, m);
		if(StrCompare_Sq(sub, T) != 0)
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	return 0;
}


// 定长顺序存储表示：串赋值 StrAssign(&T, chars)
/* 将一个char类型的数组chars赋值给SString类型的T */
Status StrAssign_Sq(SString &T, char chars[])
{
	int i = 0;
	T.length = 0;
	while(chars[i] != '\0')
	{
		T.data[i] = chars[i];
		i++;
	}
	T.length = i;

	return OK;
}


// 串的堆分配：串赋值 StrAssign(&T, chars)
/* 将一个char类型的数组chars赋值给HString类型的T */
Status StrAssign_H(HString &T, char *chars)
{
	if(T.ch)      // 重新分配T空间
	{
		T.ch = NULL;
		T.length = 0;
	}
	
	int i = 0;
	while (chars[i] != '\0') // 求char长度
	{
		i++;
	}

	if(!i)
	{
		T.ch = NULL;
		T.length = 0;
	}
	else
	{
		T.ch = (char *)malloc(i * sizeof(char));
		if(!T.ch)
		{
			exit(OVERFLOW);
		}

		for(int j = 0; j < i; j++)  // 插入T
		{
			T.ch[j] = chars[j];
		}
		T.length = i;
	}
	
	return OK;
}


// 串的堆分配：求串长StrLength(S)
/* 返回S的元素个数，即串的长度。*/
int StrLength_H(HString S)
{
	return S.length;
}


// 串的堆分配的遍历输出
Status StrTraverse_H(HString S)
{
	int len = StrLength_H(S);
	cout << "长度为：" << len << ", 遍历：";
	for(int i = 0; i < len; i++)
	{
		cout << S.ch[i];
	}
	cout << endl;

	return OK;
}


// 串的堆分配：比较大小StrCompare(S,T)
/* 若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0。*/
int StrCompare_H(HString S, HString T)
{
	for(int i = 0; i < S.length && i < T.length; i++)
	{
		if(S.ch[i] != T.ch[i])
		{
			return S.ch[i] - T.ch[i];
		}
	}

	return S.length - T.length;
}



// 串的堆分配：清空串ClearString(&S)
/* 将S清为空串 */
Status ClearString_H(HString &S)
{
	if(S.ch)
	{
		free(S.ch);
		S.ch = NULL;
	}

	S.length = 0;
	return OK;
}


// 串的堆分配：串联接Contcat(&T, S1, S2)
/* 用T返回由S1和S2串联接而成的新串。*/
Status Concat_H(HString &T, HString S1, HString S2)
{
	T.ch = (char *)malloc((S1.length + S2.length) * sizeof(char));
	T.length = 0;
	if(!T.ch)
	{
		exit(OVERFLOW);
	}

	for(int i = 0; i < S1.length; i++)
	{
		T.ch[i] = S1.ch[i];
	}

	for(int j = 0; j < S2.length; j++)
	{
		T.ch[S1.length + j] = S2.ch[j];
	}

	T.length = S1.length + S2.length;
	return OK;
}


// 串的堆分配：求子串SubString(&Sub, S, pos, len)
/* 用Sub返回S的第pos个字符起长度为len的子串。
   其中，1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1。*/
Status SubString_H(HString &Sub, HString S, int pos, int len)
{
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
	{
		return ERROR;
	}

	if(Sub.ch)       // 释放旧空间
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}

	if(!len)  // 空子串
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}
	else 
	{
		Sub.ch = (char *)malloc(len * sizeof(char));
		for(int i = 0; i < len; i++)
		{
			Sub.ch[i] = S.ch[pos+ i - 1];
		}
		Sub.length = len;
	}

	return OK;
}


// 算法4.4，串的堆分配：插入操作StrInsert(&S, pos, T)
/* 在串S的第pos个字符前插入串T，1<=pos<=StrLength(S)+1. */
Status StrInsert_H(HString &S, int pos, HString T)
{
	if(pos < 1 || pos > S.length + 1)   // pos不合法
	{
		return ERROR;
	}

	if(T.length) // T非空，则重新分配空间，插入T
	{
		S.ch = (char *)realloc(S.ch, (S.length + T.length) * sizeof(char));
		if(!S.ch)  // 存储空间分配失败
		{
			exit(OVERFLOW);
		}
		
		for(int i = S.length - 1; i >= pos - 1; i--)  // 为插入T而腾出位置
		{
			S.ch[i + T.length] = S.ch[i];
		}

		for(int j = 0; j < T.length; j++)  // 插入T
		{
			S.ch[pos - 1 + j] = T.ch[j];
		}
		S.length += T.length;
	}
	else   // T空
	{
		S.ch = (char *)malloc(T.length * sizeof(char));
		if(!S.ch)  // 存储空间分配失败
		{
			exit(OVERFLOW);
		}

		for(int j = 0; j < T.length; j++)  // 插入T
		{
			S.ch[pos - 1 + j] = T.ch[j];
		}
		S.length = T.length;
	}

	return OK;
}


// 定位函数Index(S, T, pos)
/* T为非空串，若主串S中第pos个字符之后存在与T相等的子串，
   则返回第一个这样的子串在S中的位置，否则返回0。*/
int Index_H(HString S, HString T, int pos)
{
	if(pos <= 0)
	{
		return 0;
	}
	
	HString sub;
	int n, m, i;
	n = StrLength_H(S);
	m = StrLength_H(T);
	i = pos;
	while(i < n - m + 1)
	{
		SubString_H(sub, S, i, m);
		if(StrCompare_H(sub, T) != 0)
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	return 0;
}


// 定长顺序串的基本操作具体实现实例
void DisplaySeqStrings()
{
	char chars1[] = "ABCDEFG";
	char chars2[] = "BCDEF";
	SString T, S, M;
	StrAssign_Sq(T, chars1);
	StrAssign_Sq(S, chars2);
	cout << "字符串T";
	StrTraverse_Sq(T);
	cout << "字符串S";
	StrTraverse_Sq(S);
	cout << "S和T的比较结果：" << StrCompare_Sq(S, T);
	Concat_Sq(M, T, S);
	cout << "\nS和T的拼接结果，新的字符串M";
	StrTraverse_Sq(M);
	cout << "子串S是否存在T中? " << Index_Sq(T, S, 1);
}


// 堆分配串的基本操作具体实现实例
void DisplayHStrings()
{
	char chars1[] = "ABCDEFG";
	char chars2[] = "BCDEF";
	HString T, S, M;
	StrAssign_H(T, chars1);
	StrAssign_H(S, chars2);
	cout << "字符串T";
	StrTraverse_H(T);
	cout << "字符串S";
	StrTraverse_H(S);
	cout << "S和T的比较结果：" << StrCompare_H(S, T);
	Concat_H(M, T, S);
	cout << "\nS和T的拼接结果，新的字符串M";
	StrTraverse_H(M);
	cout << "子串S是否存在T中? " << Index_H(T, S, 1);
	StrInsert_H(S, 4, T);
	cout << "\n在串S的第4个字符前插入串T: ";
	StrTraverse_H(S);
	cout << "串S清空中... " << ClearString_H(T);
}


// 测试函数
void TestStrings()
{
	cout << "==============串的基本操作及其相关算法演示================\n" << endl;
	cout << "==============定长顺序串的基本操作具体实现实例================\n" << endl;
	DisplaySeqStrings();
	cout << "\n\n==============堆分配串的基本操作具体实现实例================\n" << endl;
	DisplayHStrings();
}
