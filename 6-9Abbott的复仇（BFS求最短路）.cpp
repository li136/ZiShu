/*
 UVa 816
 问题描述：
 有一个最多包含9*9个交叉点的迷宫。
 输入起点、离开起点的朝向和终点。求一条最短路。（多解时任意输入一个即可）
 迷宫特殊之处在于进入每一个交叉点de方向不同，允许出去的方向也不同。
 例：  1 2 WLF NR ER *   表示交叉点(1，2)有3个路标（字符*是结束标志）
 NEWS分别表示北东西南。LFR表示左转，直行，右转。
*/

/*
 例：
SAMPLE 3 1 N 3 3 
1 1 WL NR * 
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0 
*/

#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

struct Node 
{
	int r, c, dir; // 站在(r,c)，面朝方向dir(0~3分别表示N, E, S, W)
	Node(int r = 0, int c = 0, int dir = 0) :r(r), c(c), dir(dir) {}
};

const int maxn = 10;
const char* dirs = "NESW"; // 顺时针旋转
const char* turns = "FLR";

int has_edge[maxn][maxn][4][3];//两个坐标，方向，转向。记录朝向是怎么过来的。
int d[maxn][maxn][4];
Node p[maxn][maxn][4];
int r0, c0, dir, r1, c1, r2, c2;//0为起点，2为终点。

int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

Node walk(const Node& u, int turn)
{
	int dir = u.dir;
	if (turn == 1) dir = (dir + 3) % 4; // 逆时针
	if (turn == 2) dir = (dir + 1) % 4; // 顺时针
	return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

bool inside(int r, int c) 
{
	return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

bool read_case() 
{
	char s[99], s2[99];
	if (scanf("%s%d%d%s%d%d", s, &r0, &c0, s2, &r2, &c2) != 6) return false;
	printf("%s\n", s);

	dir = dir_id(s2[0]);//方向字符“标准化”
	r1 = r0 + dr[dir];//第一步的坐标
	c1 = c0 + dc[dir];

	memset(has_edge, 0, sizeof(has_edge));//has_edge状态还原。
	for (;;) 
	{
		int r, c;
		scanf("%d", &r);
		if (r == 0) break;
		scanf("%d", &c);
		while (scanf("%s", s) == 1 && s[0] != '*') 
		{
			for (int i = 1; i < strlen(s); i++)
				has_edge[r][c][dir_id(s[0])][turn_id(s[i])] = 1;
		}
	}
	return true;
}

void print_ans(Node u) 
{
	// 从目标结点逆序追溯到初始结点
	vector<Node> nodes;//vector方便p的记录p的反向递推。
	for (;;) 
	{
		nodes.push_back(u);
		if (d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(Node(r0, c0, dir));

	// 打印解，每行10个
	int cnt = 0;
	for (int i = nodes.size() - 1; i >= 0; i--) 
	{
		if (cnt % 10 == 0) printf(" ");
		printf(" (%d,%d)", nodes[i].r, nodes[i].c);
		if (++cnt % 10 == 0) printf("\n");
	}
	if (nodes.size() % 10 != 0) printf("\n");
}

void solve() 
{
	queue<Node> q;
	memset(d, -1, sizeof(d));//d状态还原
	Node u(r1, c1, dir);//用初始位置初始化u,u是当前位置。
	d[u.r][u.c][u.dir] = 0;
	q.push(u);
	while (!q.empty()) 
	{
		Node u = q.front(); q.pop();//和上一个u不是同一个，新建一个Node
		if (u.r == r2 && u.c == c2) { print_ans(u); return; }//到达终点。
		for (int i = 0; i < 3; i++) //3个方向
		{
			Node v = walk(u, i);//先不管条件，判断下一步状态。但不记录在u上，记录在新建的v上。
			//记录两个前后坐标的原因在于1：方便接下来的if条件判断。2：if条件用到后一个位置，语句内要用到前一个位置。

			//方向是否能走&&是否在原范围内&&是否原样走过。
			if (has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) 
			{
				//因为是BFS，所以一定是最快的到达的该朝向及位置。
				d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;//上一个点的值再加一。
				p[v.r][v.c][v.dir] = u;//p的意义是在后一坐标存储前一坐标的位置。
				q.push(v);
			}
		}
	}
	printf("  No Solution Possible\n");
}

int main() 
{
	while (read_case()) 
	{
		solve();
	}
	return 0;
}