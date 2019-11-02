/*
UVa1601 The Morning after Halloween

w h （w, h <= 16)的网格有 n （ n <= 3) 个小写字母（代表鬼）
其余的是‘#’（代表障碍格） 或 ‘ ’（代表空格。
 要求把他们移动到对应的大写字母里。
 每步可以有多少个鬼同时移动（均为上下左右4个移动方向之一）， 
 但每步移动两个鬼不能占用同一个位置， 也不能在一步之内交换位置。
输入保证空格联通，障碍联通，且在2 2子网格中至少有一个障碍格，并且最外面一层是障碍格。
输入保证有解。
*/

//邻接表优化入口，免除#不通的判断。
//

#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
using namespace std;

const int maxs = 20;
const int maxn = 150; // 75% cells plus 2 fake nodes
const int dx[] = { 1,-1,0,0,0 }; // 4 moves, plus "no move"
const int dy[] = { 0,0,1,-1,0 };

inline int ID(int a, int b, int c) 
{ 
	return (a << 16) | (b << 8) | c;
}

int s[3], t[3]; // 起点和终点

int deg[maxn], G[maxn][5]; // target cells for each move (including "no move")

inline bool conflict(int a, int b, int a2, int b2) 
{
	return a2 == b2 || (a2 == b && b2 == a);
}

int d[maxn][maxn][maxn]; // distance from starting state

int bfs()
{
	queue<int> q;
	memset(d, -1, sizeof(d));
	q.push(ID(s[0], s[1], s[2])); // starting node
	d[s[0]][s[1]][s[2]] = 0;

	while (!q.empty()) 
	{
		int u = q.front(); q.pop();
		int a = (u >> 16) & 0xff, b = (u >> 8) & 0xff, c = u & 0xff;//ID解码为a,b,c的编号
		if (a == t[0] && b == t[1] && c == t[2]) return d[a][b][c]; // solution found
		for (int i = 0; i < deg[a]; i++) 
		{
			int a2 = G[a][i];
			for (int j = 0; j < deg[b]; j++) 
			{ 
				int b2 = G[b][j];
				if (conflict(a, b, a2, b2)) continue;
				for (int k = 0; k < deg[c]; k++) 
				{
					int c2 = G[c][k];
					if (conflict(a, c, a2, c2)) continue;
					if (conflict(b, c, b2, c2)) continue;

					if (d[a2][b2][c2] != -1) continue;//该状态是否走过

					d[a2][b2][c2] = d[a][b][c] + 1;
					q.push(ID(a2, b2, c2));
				}
			}
		}
	}
	return -1;
}

int main() 
{
	int w, h, n;

	while (scanf("%d%d%d\n", &w, &h, &n) == 3 && n) 
	{
		char maze[20][20];
		for (int i = 0; i < h; i++)
			fgets(maze[i], 20, stdin);

		// 提取 empty cells
		int cnt, x[maxn], y[maxn], id[maxs][maxs]; // cnt is the number of empty cells
		cnt = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (maze[i][j] != '#') 
				{
					x[cnt] = i; y[cnt] = j; id[i][j] = cnt;//每一个空节点的x,y坐标和对应的索引编号
					//入口出口额外增加一个s、t数组对应其编号
					if (islower(maze[i][j])) s[maze[i][j] - 'a'] = cnt;//字母和编号索引
					else if (isupper(maze[i][j])) t[maze[i][j] - 'A'] = cnt;
					//每一个非#结点都会让cnt++
					cnt++;
				}

		// 建立对应邻接表
		for (int i = 0; i < cnt; i++) 
		{
			deg[i] = 0;
			for (int dir = 0; dir < 5; dir++) 
			{
				int nx = x[i] + dx[dir], ny = y[i] + dy[dir];//新的位置坐标
				// “地图最外层的单元格是墙”意味着我们不需要检查出边界，直接检查是否是#
				if (maze[nx][ny] != '#') //deg[i]++来表示该编号结点的度
					G[i][deg[i]++] = id[nx][ny];//建表，这里注意我们不再需要坐标，只要编号就行
			}
		}

		// add fakes nodes so that in each case we have 3 ghosts. this makes the code shorter
		if (n <= 2) { deg[cnt] = 1; G[cnt][0] = cnt; s[2] = t[2] = cnt++; }
		if (n <= 1) { deg[cnt] = 1; G[cnt][0] = cnt; s[1] = t[1] = cnt++; }

		printf("%d\n", bfs());
	}
	return 0;
}
