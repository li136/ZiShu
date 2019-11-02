/*
 问题描述：
 火车以1，2，3，4，5到n的顺序入车站（入栈），输入一个顺序，求是否是可能的出栈顺序。
*/

/*
 函数：
 push(),pop(),top(),empty()。都是常见的函数。注意这里没有用algorithm头文件。
*/
#include<cstdio>
#include<stack>
using namespace std;
const int MAXN = 1000 + 10;

int n, target[MAXN];

int main()
{
	while (scanf_s("%d", &n) == 1)//判断输入是否合法，进入循环
	{
		stack<int> s;
		int A = 1, B = 1;//
		for (int i = 1; i <= n; i++)
			scanf_s("%d", &target[i]);
		int ok = 1;
		while (B <= n)
		{
			if (A == target[B])//不经过栈直接输出
			{
				A++; B++;
			}
			else if (!s.empty() && s.top() == target[B])//出栈
			{
				s.pop(); B++;
			}
			else if (A <= n)//入栈
				s.push(A++);
			else
			{
				ok = 0; break;
			}
		}
		printf("%s\n", ok ? "Yes" : "No");//很有用的小技巧，减少一个if语句，更清晰，直观。
	}
	return 0;
}