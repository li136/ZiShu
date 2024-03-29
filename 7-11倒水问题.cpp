/*
UVa10603 Fill
问题描述：
给定大小分别为a,b,c容量的杯子，c杯装满水。得到目标水量x
求倒水的最小水量和目标水量

样例输入：先输入次数n，然后每行依次为a,b,c,x
2
2 3 4 2
96 97 199 62
输出：
2 2
9859 62
*/ 

#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct Node 
{
	int v[3], dist;
	bool operator < (const Node& rhs) const 
    {
		return dist > rhs.dist;
	}
};

const int maxn = 200 + 5;
int mark[maxn][maxn], dist[maxn][maxn], cap[3], ans[maxn];

void update_ans(const Node& u) 
{
	for (int i = 0; i < 3; i++) 
    {
		int d = u.v[i];
		if (ans[d] < 0 || u.dist < ans[d]) ans[d] = u.dist;
	}
}

void solve(int a, int b, int c, int d) 
{
	cap[0] = a; cap[1] = b; cap[2] = c;
	memset(ans, -1, sizeof(ans));
	memset(mark, 0, sizeof(mark));
	memset(dist, -1, sizeof(dist));
	priority_queue<Node> q;

	Node start;
	start.dist = 0;
	start.v[0] = 0; start.v[1] = 0; start.v[2] = c;
	q.push(start);

	dist[0][0] = 0;
    
	while (!q.empty()) 
    {
		Node u = q.top(); q.pop();
		if (mark[u.v[0]][u.v[1]]) continue;
		mark[u.v[0]][u.v[1]] = 1;
		update_ans(u);

		if (ans[d] >= 0) break;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) if (i != j) 
            {
				if (u.v[i] == 0 || u.v[j] == cap[j]) continue;
				int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
				Node u2;
				memcpy(&u2, &u, sizeof(u));
				u2.dist = u.dist + amount;
				u2.v[i] -= amount;
				u2.v[j] += amount;
				int& D = dist[u2.v[0]][u2.v[1]];
				if (D < 0 || u2.dist < D) 
                {//dist数组存在的意义是记录当前状态的最小值，以免垃圾状态进入优先队列中
					D = u2.dist;
					q.push(u2);
				}
			}
	}
	while (d >= 0) 
    {
		if (ans[d] >= 0) 
        {
			printf("%d %d\n", ans[d], d);
			return;
		}
		d--;
	}
}

int main() 
{
	int T, a, b, c, d;
	scanf("%d", &T);
	while (T--) 
    {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		solve(a, b, c, d);
	}
	return 0;
}
