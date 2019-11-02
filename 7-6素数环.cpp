/*
Uva 524 Prime Ring Problem

输入正整数n，吧整数1~n个数组成一个环，使得相邻两个整数之和均为素数。
输出从一开始逆时针排列，每个环恰好输出一次。n<=16

样例输入：
6
输出：
1 4 3 2 5 6
1 6 5 2 3 4
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int is_prime(int x) //判断是否为素数
{
	for (int i = 2; i*i <= x; i++)
		if (x % i == 0) return 0;
	return 1;
}

int n, A[50], isp[50], vis[50];

void dfs(int cur) 
{
	if (cur == n && isp[A[0] + A[n - 1]])//判断是否是最后一个元素且满足条件
    {
		for (int i = 0; i < n; i++) //打印解
        {
			if (i != 0) printf(" ");
			printf("%d", A[i]);
		}
		printf("\n");
	}
	else for (int i = 2; i <= n; i++)//继续递归
		if (!vis[i] && isp[i + A[cur - 1]]) 
        {
			A[cur] = i;
			vis[i] = 1;
			dfs(cur + 1);
			vis[i] = 0;
		}
}

int main() 
{
	int kase = 0;
	while (scanf("%d", &n) == 1 && n > 0) 
    {
		if (kase > 0) printf("\n");
		printf("Case %d:\n", ++kase);

		for (int i = 2; i <= n * 2; i++) isp[i] = is_prime(i);//素数打表

		memset(vis, 0, sizeof(vis));
		A[0] = 1; //输出首位为一
		dfs(1);
	}
	return 0;
}