/*
 UVa 10305
 问题描述:

*/

/*
每组测试数据可能有好几列。第一列有2个整数n，m。
（1 <= n <= 100）n代表共有几件事情要做（编号从1到n），m代表事情之间有几个相依关系存在。
接下来的m列每列有2个整数i和j。代表i这件事情一定要在j这件事前被执行。
n=m=0时代表输入结束。
例：
Sample Input
5 4
1 2
2 3
1 3
1 5
0 0
Sample Output
1 4 2 5 3
*/

// 算法：拓扑排序。注意m可能等于0
//该算法内在逻辑：依次循环处理所有元素，
//当检测到有一个元素在被检测元素后时，处理新元素，元素被放置在数组中（从后往前）.
//当发现有元素正在检测却还未被放置到数组（处理完毕），证明出现闭环。

#include<cstdio>
#include<cstring>
const int maxn = 1000;
int n, m, G[maxn][maxn], c[maxn], topo[maxn], t;

bool dfs(int u) 
{
	c[u] = -1;
	for (int v = 0; v < n; v++)
		if (G[u][v]) 
		{
			if (c[v] < 0) return false;
			else if (!c[v]) dfs(v);
		}
	c[u] = 1; topo[--t] = u;
	return true;
}

bool toposort() 
{
	t = n;
	memset(c, 0, sizeof(c));
	for (int u = 0; u < n; u++)
		if (!c[u]&&!dfs(u))    //这个判断用的有点巧妙的
			return false;
	return true;
}

int main() 
{
	while (scanf_s("%d%d", &n, &m) == 2 && n) 
	{
		memset(G, 0, sizeof(G));
		for (int i = 0; i < m; i++) 
		{
			int u, v;
			scanf_s("%d%d", &u, &v); u--; v--;
			G[u][v] = 1;
		}
		if (toposort()) 
		{
			for (int i = 0; i < n - 1; i++)
				printf("%d ", topo[i] + 1);
			printf("%d\n", topo[n - 1] + 1);
		}
		else
			printf("No\n"); // 题目没说无解输出什么，应该是保证有解吧
	}
}