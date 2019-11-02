 /*
UVa1374 Power Calculus
问题描述：
输入正整数n=1~1000，问x至少需要几次乘除法才能得到x的n次方。

样例输入：   31
输出         6
 */

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxans = 13; // we got it by experimenting

int n, a[maxans + 1];

bool dfs(int d, int maxd) 
{
	if (a[d] == n) return true;//得到目标
	if (d == maxd) return false;//深度限制

    //不用bfs而用迭代的原因可能就是为了剪枝吧
	int maxv = a[0];
	for (int i = 1; i <= d; i++) maxv = max(maxv, a[i]);//得到d之前的a数组的最大值
	if ((maxv << (maxd - d)) < n) return false;//这里还是剪枝

	// Always use the last value.
	// I can't prove it, but we haven't found a counter-example for n <= 1000
	for (int i = d; i >= 0; i--) 
    {
		a[d + 1] = a[d] + a[i];
		if (dfs(d + 1, maxd)) return true;
		a[d + 1] = a[d] - a[i];
		if (dfs(d + 1, maxd)) return true;
	}
	return false;
}

int solve(int n) 
{
	if (n == 1) return 0;
	a[0] = 1;
	for (int maxd = 1; maxd < maxans; maxd++)//这里还是迭代加深，还是蛮通用的。
    {
		if (dfs(0, maxd)) return maxd;
	}
	return maxans;
}

int main() 
{
	while (scanf("%d", &n) == 1 && n) 
    {
		printf("%d\n", solve(n));
	}
	return 0;
}