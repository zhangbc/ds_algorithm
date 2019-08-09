#include "stdafx.h"
#include "data_algorithm.h"

#include <string>
#include <algorithm>

#include <iostream>
using namespace std;


//  算法1.1：旋转字符串，暴力移位法
void LeftShiftOne(char* strs, int number)
{	
	int i = 0;
	char ch = strs[i];
	for(i = 1; i < number; i++)
	{
		strs[i-1] = strs[i];
	}
	strs[i-1] = ch;
}


void LeftRoatateString(char* strs, int n, int m)
{
	while(m--)
	{
		LeftShiftOne(strs, n);
	}
}


//  算法1.1：旋转字符串，三步反转法
void ReverseString(char* str, int from, int to)
{
	while(from < to)
	{
		char ch = str[from];
		str[from++] = str[to];
		str[to--] = ch;
	}
}


void LeftReverseString(char* strs, int n, int m)
{
	m %= n;
	ReverseString(strs, 0, m-1);
	ReverseString(strs, m, n-1);
	ReverseString(strs, 0, n-1);
}



// 算法1.2：字符串包含，常规方法
bool StringContain(string &a, string &b)
{
	for(int i=0; i < b.length(); i++)
	{
		int j;
		for(j=0; (j < a.length()) && (a[j] != b[i]); j++);
		if(j >= a.length())
		{
			return false;
		}
	}
	return true;
}


// 算法1.2：字符串包含，排序方法
bool StringContainSort(string &a, string &b)
{
	sort(a.begin(), a.end());   // 包含于<algorithm>模块内
	sort(b.begin(), b.end());
	for(int pa = 0, pb = 0; pb < b.length(); pb++)
	{
		while((pa < a.length()) && (a[pa] < b[pb]))
		{
			pa++;
		}
		if(pa >= a.length() || (a[pa] > b[pb]))
		{
			return false;
		}
	}
	return true;
}


// 算法1.2：字符串包含，转换成素数
bool StringContainPrime(string &a, string &b)
{
	const int array[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
		43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
	int f = 1;
	for(int i = 0; i < a.length(); i++)
	{
		int x = array[a[i] - 'A'];
		if(f % x)
		{
			f *= x;
		}
	}
	
	for(int j = 0; j < b.length(); j++)
	{
		int x = array[b[j] - 'A'];
		if(f % x)
		{
			return false;
		}
	}
	return true;
}


// 算法1.2：字符串包含，Hashtable方法
bool StringContainHash(string &a, string &b)
{
	int hash = 0;
	for(int i = 0; i < a.length(); i++)
	{
		hash |= (1 << (a[i] - 'A'));
	}
	
	for(int j = 0; j < b.length(); j++)
	{
		if(hash & (1 << (b[j] - 'A')))
		{
			return false;
		}
	}
	return true;
}


// 算法1.3：字符串转成整数
int StrToInt(const char* str)
{
	static const int MAX_INT = (int)((unsigned)~0 >> 1);
	static const int MIN_INT = -(int)((unsigned)~0 >> 1);
	unsigned int n = 0;

	// 判空
	if(str == 0)
	{
		return 0;
	}

	// 处理空格
	while(isspace(*str))
	{
		++str;
	}
	
	// 处理正负
	int sign = 1;
	if(*str == '+' || *str == '-')
	{
		if(*str == '-')
		{
			sign = -1;
		}
		str++;
	}

	while(isdigit(*str))
	{
		int c = *str - '0';
		if(sign > 0 && (n > MAX_INT/10 || (n == MAX_INT/10 && c > MAX_INT%10)))
		{
			n = MAX_INT;
			break;
		}
		else if(sign < 0 && (n > (unsigned)MIN_INT/10 || (n == (unsigned)MIN_INT/10 && c > (unsigned)MIN_INT%10)))
		{
			n = MIN_INT;
			break;
		}
		
		n = n *10 + c;
		str++;
	}
	return sign > 0 ? n:-n;
}


// 算法1.4：回文判断，首尾向中间扫描字符串
bool IsPalindrome(const char *s, int n)
{
	if(s == NULL || n < 1)
	{
		return false;
	}

	const char *front, *back;
	front = s;
	back = s + n - 1;
	while(front < back)
	{
		if(*front != *back)
		{
			return false;
		}
		++front;
		--back;
	}
	return true;
}


// 算法1.4：回文判断，中间向首尾扫描字符串
bool IsPalindromeMid(const char *s, int n)
{
	if(s == NULL || n < 1)
	{
		return false;
	}

	int front, back;
	int m = ((n >> 1) - 1) >= 0 ? (n >> 1) -1 :0; // middle point
	front = m;
	back = n - 1 - m;
	while(front >= 0)
	{
		if(s[front--] != s[back++])
		{
			return false;
		}
	}
	return true;
}


// 算法1.5：最长回文子串长度
int LongestPadlindrome(const char *s, int n)
{
	int i, j, max, c;
	if(s == NULL || n < 1)
	{
		return 0;
	}

	max = 0;
	for(i = 1; i < n; i++)
	{
		if(max < 2 && s[i] == s[i - 1])  // 解决s="AABC"问题
		{
			max = 2;
		}

		for(j = 0; (i - j >= 0) && (i + j < n); j++)
		{
			if(s[i - j] != s[i + j])
			{
				break;
			}
			c = j * 2 + 1;
		}

		if(c > max)
		{
			max = c;
		}
		
		for(j = 0; (i - j >= 0) && (i + j + 1 < n); j++) 
		{
			if(s[i - j] != s[i + j + 1])
			{
				break;
			}
			c = j * 2 + 2;
		}
		
		if(c > max)
		{
			max = c;
		}
	}
	return max;
}


// Manacher算法
int Manacher(string s, int len)
{
	int *p = new int[len];
	int maxLen = -1;
	int id=0, mx = 0;
	for(int i = 0; i < len; i++)
	{
		if(i < mx)
		{
			p[i] = p[2 * id - i] < mx - i ? p[2 * id - i] :  mx - i;
		}
		else 
		{
			p[i] = 1;
		}

		while(s[i - p[i]] == s[i + p[i]])
		{
			p[i]++;
		}

		if(mx < i + p[i])
		{
			mx = i + p[i];
			id = i;
		}
		maxLen = maxLen > p[i] - 1 ? maxLen : p[i] - 1;
	}
	return maxLen;
}


// 算法1.5：最长回文子串长度, Manacher算法
int LongestPadlindromeMancher(const char *s, int n)
{
	char *new_s = new char[n*2];
	int j = 0;
	new_s[j++] = '$';
	new_s[j++] = '#';
	for(int i = 0; i < n; i++)
	{
		new_s[j++] = s[i];
		new_s[j++] = '#';
	}
	new_s[j] = '\0';
	int maxLen = Manacher(new_s, j-1);
	return maxLen;
}


// 算法1.6：字符串的全排列，递归法，"AACD"重复排序问题
void CalcAllPermutationRec(char *perm, int from, int to)
{
	if(to <= 1)
	{
		return;
	}

	if(from == to)
	{
		cout << perm << endl;
	}
	else
	{
		for(int j = from; j <= to; j++)
		{
			swap(perm[j], perm[from]);
			CalcAllPermutationRec(perm, from + 1, to);
			swap(perm[j], perm[from]);           
		}
	}
}


// 算法1.6：字符串的全排列，字典序排列法
bool CalcAllPermutationDic(char *perm, int num)
{
	int i;
	// ① 找到排列中最后(最右)一个升序的首位位置i，x=ai
	for(i = num - 2; (i >= 0) && (perm[i] >= perm[i + 1]); i--)
	{
		;
	}

	// 已经找到所有排序
	if(i < 0)
	{
		return false;
	}
	
	int k;
	// ② 找到排列中第i个右边最后一个比ai大的位置j，y=aj
	for(k = num - 1; (k > i) && (perm[k] <= perm[i]); k--)
	{
		;
	}

	// ③ 交换x，y
	swap(perm[i], perm[k]);

	// ④ 把第(i+1)位到最后的部分翻转
	reverse(perm + i + 1, perm + num);
	return true;
}


// 测试函数
void test_strings()
{	
	char strs1[] = "ABCDEFGH";
	cout << "原字符串为：" << strs1 << endl;
	LeftRoatateString(strs1, 8, 2);
	cout << "算法1.1：旋转字符串，暴力移位法:" << strs1 << endl;
	
	char strs2[] = "ABCDEFGH";
	LeftReverseString(strs2, 8, 2);
	cout << "算法1.1：旋转字符串，三步反转法:" << strs2 << endl;
	cout << "==================================\n" << endl;
	
	
	string a = "ABACCD";
	string b = "ABV";
	cout << "字符串A：" << a << "，是否包含字符串B: " << b << "?" << endl;
	bool result = StringContain(a, b);
	cout << "算法1.2：字符串包含，常规方法: " << result << endl;
	result = StringContainSort(a, b);
	cout << "算法1.2：字符串包含，排序方法: " << result << endl;
	result = StringContainPrime(a, b);
	cout << "算法1.2：字符串包含，排序方法: " << result << endl;
	result = StringContainHash(a, b);
	cout << "算法1.2：字符串包含，Hashtable方法: " << result << endl;
	cout << "==================================\n" << endl;
	
	char str[] = "-12.32312";
	cout << "原字符串为：" << str << endl;
	cout << "算法1.3：字符串转成整数：" << StrToInt(str) << endl;
	cout << "==================================\n" << endl;

	char st[] = "ABCDCBA";
	cout << "原字符串为：" << st << endl;
	result = IsPalindrome(st, 7);
	cout << "算法1.4：回文判断，首尾向中间扫描字符串：" << result << endl;
	result = IsPalindromeMid(st, 7);
	cout << "算法1.4：回文判断，中间向首尾扫描字符串：" << result << endl;
	cout << "==================================\n" << endl;
	
	char str_len[] = "ABCDCBAABBA";
	int res = LongestPadlindrome(str_len, 11);
	cout << "算法1.5：最长回文子串长度：" << res << endl;
	res = LongestPadlindromeMancher(str_len, 11);
	cout << "算法1.5：最长回文子串长度, Manacher算法：" << res << endl;
	cout << "==================================\n" << endl;

	char perm[] = "ABCD";
	cout << "算法1.6：字符串的全排列，递归法：" << endl;
	CalcAllPermutationRec(perm, 0, 3);  // 从下标零开始
	
	cout << "\n算法1.6：字符串的全排列，字典序排列：" << endl;
	bool flag;
	cout << perm << endl;
	while(true)
	{
		flag = CalcAllPermutationDic(perm, strlen(perm));
		if (flag == false)
		{
			break;
		}
		cout << perm << endl;
	}
}