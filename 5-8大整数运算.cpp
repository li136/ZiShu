/*
 问题描述：
 处理大整数（正）的加减乘除运算
*/

/*
 用vector<int>保存元素，用struct建立Big类。
 使用函数：
         clear()清空数组（例如vector）的元素。
		 push_back()在vector尾后添加新元素。
		 length()输出数组（例如string）元素个数。
		 max()输出两个元素中较大的那个数。
		 sscanf_s()将字符串转换格式输入到其他变量。
		 substr()输入前后两个数组指针，输出对应的新字符串
		 c_str()返回一个临时的字符串指针
		 sprintf_s()结果输出到指定的字符串中。
*/




#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//大整数类
struct Big
{
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int>s;

	Big(long long num=0)
	{
		*this = num;
	}

	Big& operator =(long long num)//long long int类型赋值---num
	{
		s.clear();
		do
		{
			s.push_back(num%BASE);//添加num的后8位
			num /= BASE;          //num减去后8位
		} while (num > 0);
		return *this;             //返回类
	}

	Big& operator =(const string& str)
	{
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;//length()函数返回字节数
		for (int i = 0; i < len; i++)
		{
			int end = str.length() - i * WIDTH;
			int start = max(0, end - WIDTH);
			sscanf(str.substr(start, end - start).c_str(), "%d", &x);//原为sscanf()函数
			s.push_back(x);
		}
		return *this; 
	}

	Big operator + (const Big& b)const
	{
		Big c;
		c.s.clear();
		for (int i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = g;
			if (i < s.size())
				x += s[i];
			if (i < b.s.size())
				x += b.s[i];
			c.s.push_back(x%BASE);
			g = x / BASE;
		}
		return c;
	}
};

ostream & operator <<(ostream &out, const Big &x)
{
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--)
	{
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);    //巧妙！！！-原为sprintf()函数。将123转化为00000123
		for (int j = 0; j < strlen(buf); j++)
			out << buf[j];
	}
	return out;
}

istream & operator >>(istream &in, Big &x)
{
	string s;
	if (!(in >> s))
		return in;
	x = s;
	return in;
}

int main()
{
	Big a, b;
	cin >> a >> b;
	cout << a + b;
	int n; cin >> n;
	return 0;
}