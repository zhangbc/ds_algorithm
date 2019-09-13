#include "stdafx.h"
#include "math.h"
#include "stdlib.h"
#include "data_structure.h"


#include <iostream>
using namespace std;


typedef struct 
{
	unsigned char data[MAXSTRLEN];           // ����Ԫ��
	int length;                              // ���ĳ���   
}SString;                                    // ���Ķ���˳��洢�ṹ


typedef struct
{
	char *ch;     // ���Ƿǿմ������մ�������洢��������chΪNULL
	int length;   // ���ĳ���
}HString;         // ���Ķѷ���洢�ṹ



typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;


typedef struct
{
	Chunk *head, *tail;   // ����ͷ��βָ��
	int curlen;           // c���ĵ�ǰ����
}LString;


// ����˳��洢��ʾ���󴮳�StrLength(S)
/* ����S��Ԫ�ظ����������ĳ��ȡ�*/
int StrLength_Sq(SString S)
{
	return S.length;
}


// ����˳��洢��ʾ���Ƚϴ�СStrCompare(S,T)
/* ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0��*/
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


// ����˳�򴮵ı������
Status StrTraverse_Sq(SString S)
{
	int len = S.length;
	cout << "����Ϊ��" << len << ", ������";
	for(int i = 0; i < len; i++)
	{
		cout << S.data[i];
	}
	cout << endl;

	return OK;
}


// ����˳��洢��ʾ��������StrCopying(&T, S, pos, len)
/* ������S��ǰlen����ɵ����Ӵ���
   ��δ�ضϣ��ڷ���TRUE�����򷵻�FALSE��
   ���У�0<len<=S.length��len<=T.length+pos��T.length<pos<=MAXSTRLEN��*/
Status StrCopying(SString &T, SString S, int pos, int len)
{
	Status uncat;
	int length, j = 0;
	/* ������T����ʼλ���ѱ�ռ�û���T�����������߸��Ƴ���С��1�����Ϸ���*/
	if(pos < T.length || pos > MAXSTRLEN || len < 1 || T.length == MAXSTRLEN)   
	{
		return ERROR;
	}

	if(len > S.length)  // ���ȷǷ�������S[0]
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


// �㷨4.2������˳��洢��ʾ��������Contcat(&T, S1, S2)
/* ��T������S1��S2���Ӷ��ɵ��´�����δ�ضϣ��ڷ���TRUE�����򷵻�FALSE��*/
Status Concat_Sq(SString &T, SString S1, SString S2)
{
	Status uncat;
	T.length = 0;
	if(S1.length + S2.length <= MAXSTRLEN)  // δ�ض�
	{
		StrCopying(T, S1, 1, S1.length);
		StrCopying(T, S2, T.length+1, S2.length);
		uncat = TRUE;
	}
	else if(S1.length < MAXSTRLEN)     // �ض�(ȡS2����)
	{
		StrCopying(T, S1, 1, S1.length);
		StrCopying(T, S1, T.length + 1, MAXSTRLEN - T.length);
		uncat = FALSE;
	}
	else                           // �ض�(��ȡS1)
	{
		StrCopying(T, S1, 1, S1.length);
		uncat = FALSE;
	}

	return uncat;
}


// �㷨4.3������˳��洢��ʾ�����Ӵ�SubString(&Sub, S, pos, len)
/* ��Sub����S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
   ���У�1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos+1��*/
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


// �㷨4.1����λ����Index(S, T, pos)
/* TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
   �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0��*/
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


// ����˳��洢��ʾ������ֵ StrAssign(&T, chars)
/* ��һ��char���͵�����chars��ֵ��SString���͵�T */
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


// ���Ķѷ��䣺����ֵ StrAssign(&T, chars)
/* ��һ��char���͵�����chars��ֵ��HString���͵�T */
Status StrAssign_H(HString &T, char *chars)
{
	if(T.ch)      // ���·���T�ռ�
	{
		T.ch = NULL;
		T.length = 0;
	}
	
	int i = 0;
	while (chars[i] != '\0') // ��char����
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

		for(int j = 0; j < i; j++)  // ����T
		{
			T.ch[j] = chars[j];
		}
		T.length = i;
	}
	
	return OK;
}


// ���Ķѷ��䣺�󴮳�StrLength(S)
/* ����S��Ԫ�ظ����������ĳ��ȡ�*/
int StrLength_H(HString S)
{
	return S.length;
}


// ���Ķѷ���ı������
Status StrTraverse_H(HString S)
{
	int len = StrLength_H(S);
	cout << "����Ϊ��" << len << ", ������";
	for(int i = 0; i < len; i++)
	{
		cout << S.ch[i];
	}
	cout << endl;

	return OK;
}


// ���Ķѷ��䣺�Ƚϴ�СStrCompare(S,T)
/* ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0��*/
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



// ���Ķѷ��䣺��մ�ClearString(&S)
/* ��S��Ϊ�մ� */
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


// ���Ķѷ��䣺������Contcat(&T, S1, S2)
/* ��T������S1��S2�����Ӷ��ɵ��´���*/
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


// ���Ķѷ��䣺���Ӵ�SubString(&Sub, S, pos, len)
/* ��Sub����S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
   ���У�1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos+1��*/
Status SubString_H(HString &Sub, HString S, int pos, int len)
{
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
	{
		return ERROR;
	}

	if(Sub.ch)       // �ͷžɿռ�
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}

	if(!len)  // ���Ӵ�
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


// �㷨4.4�����Ķѷ��䣺�������StrInsert(&S, pos, T)
/* �ڴ�S�ĵ�pos���ַ�ǰ���봮T��1<=pos<=StrLength(S)+1. */
Status StrInsert_H(HString &S, int pos, HString T)
{
	if(pos < 1 || pos > S.length + 1)   // pos���Ϸ�
	{
		return ERROR;
	}

	if(T.length) // T�ǿգ������·���ռ䣬����T
	{
		S.ch = (char *)realloc(S.ch, (S.length + T.length) * sizeof(char));
		if(!S.ch)  // �洢�ռ����ʧ��
		{
			exit(OVERFLOW);
		}
		
		for(int i = S.length - 1; i >= pos - 1; i--)  // Ϊ����T���ڳ�λ��
		{
			S.ch[i + T.length] = S.ch[i];
		}

		for(int j = 0; j < T.length; j++)  // ����T
		{
			S.ch[pos - 1 + j] = T.ch[j];
		}
		S.length += T.length;
	}
	else   // T��
	{
		S.ch = (char *)malloc(T.length * sizeof(char));
		if(!S.ch)  // �洢�ռ����ʧ��
		{
			exit(OVERFLOW);
		}

		for(int j = 0; j < T.length; j++)  // ����T
		{
			S.ch[pos - 1 + j] = T.ch[j];
		}
		S.length = T.length;
	}

	return OK;
}


// ��λ����Index(S, T, pos)
/* TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
   �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0��*/
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


// ����˳�򴮵Ļ�����������ʵ��ʵ��
void DisplaySeqStrings()
{
	char chars1[] = "ABCDEFG";
	char chars2[] = "BCDEF";
	SString T, S, M;
	StrAssign_Sq(T, chars1);
	StrAssign_Sq(S, chars2);
	cout << "�ַ���T";
	StrTraverse_Sq(T);
	cout << "�ַ���S";
	StrTraverse_Sq(S);
	cout << "S��T�ıȽϽ����" << StrCompare_Sq(S, T);
	Concat_Sq(M, T, S);
	cout << "\nS��T��ƴ�ӽ�����µ��ַ���M";
	StrTraverse_Sq(M);
	cout << "�Ӵ�S�Ƿ����T��? " << Index_Sq(T, S, 1);
}


// �ѷ��䴮�Ļ�����������ʵ��ʵ��
void DisplayHStrings()
{
	char chars1[] = "ABCDEFG";
	char chars2[] = "BCDEF";
	HString T, S, M;
	StrAssign_H(T, chars1);
	StrAssign_H(S, chars2);
	cout << "�ַ���T";
	StrTraverse_H(T);
	cout << "�ַ���S";
	StrTraverse_H(S);
	cout << "S��T�ıȽϽ����" << StrCompare_H(S, T);
	Concat_H(M, T, S);
	cout << "\nS��T��ƴ�ӽ�����µ��ַ���M";
	StrTraverse_H(M);
	cout << "�Ӵ�S�Ƿ����T��? " << Index_H(T, S, 1);
	StrInsert_H(S, 4, T);
	cout << "\n�ڴ�S�ĵ�4���ַ�ǰ���봮T: ";
	StrTraverse_H(S);
	cout << "��S�����... " << ClearString_H(T);
}


// ���Ժ���
void TestStrings()
{
	cout << "==============���Ļ���������������㷨��ʾ================\n" << endl;
	cout << "==============����˳�򴮵Ļ�����������ʵ��ʵ��================\n" << endl;
	DisplaySeqStrings();
	cout << "\n\n==============�ѷ��䴮�Ļ�����������ʵ��ʵ��================\n" << endl;
	DisplayHStrings();
}
