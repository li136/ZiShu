/*
 UVa 572
 问题描述：
 输入一个m行n列的字符矩阵，统计字符“@”组成多少个八连块。
 如果两个字符“@”所在的格子相邻（横、竖、对角线方向）则属于一个同一个八连块。
 求多维数组连通块的过程也称为种子填充( floodfill )

 例：
****@
*@@*@
*@**@
@@@*@
@@**@

 有两个八连块。
*/

// 题意：输入一个字符矩阵，统计字符@组成多少个四连块
#include<cstdio>
#include<cstring>
const int maxn = 100 + 5;

char pic[maxn][maxn];
int m, n, idx[maxn][maxn];
//用了两个二维数组，一个用来记录图数据，
//一个用来记录字符所在的连接块编号，是否已被编号。

void dfs(int r, int c, int id) 
{
	if (r < 0 || r >= m || c < 0 || c >= n) return;//坐标过界处理
	if (idx[r][c] > 0 || pic[r][c] != '@') return;//查询坐标是否已被处理
	idx[r][c] = id;//坐标赋值。
	for (int dr = -1; dr <= 1; dr++)//循环遍历。
		for (int dc = -1; dc <= 1; dc++)
			if (dr != 0 || dc != 0) dfs(r + dr, c + dc, id);//对四周坐标递归
}

int main() 
{
	while (scanf_s("%d%d", &m, &n) == 2 && m && n)  
	{
		for (int i = 0; i < m; i++) scanf_s("%s", pic[i],maxn);
		memset(idx, 0, sizeof(idx));
		int cnt = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (idx[i][j] == 0 && pic[i][j] == '@') dfs(i, j, ++cnt);
		printf("%d\n", cnt);
	}
	return 0;
}