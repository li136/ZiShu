/*
 UVa 12171
 问题描述：
某雕塑由 n (n<=50) 个边平行于坐标轴的长方体组成。
每个长方体用 6 个整数 x0, y0, z0, x, y, z 表示(1<= x0, y0, z0, x, y, z <= 500)。
x0 为长方体顶点中，x 坐标的最小值，x 表示长方体在 x 方向的长度。其他 4 个值类似定义。
统计这个雕像的体积和表面积。注意，雕像内部可能会有密闭的空间，其体积应该算在总体积中。

例样输入：
2
2
1 2 3 3 4 5
6 2 3 3 4 5
7
1 1 1 5 5 1
1 1 10 5 5 1
1 1 2 1 4 8
2 1 2 4 1 8
5 2 2 1 4 8
1 5 2 4 1 8
3 3 4 1 1 1
例样输出：
188 120
250 250

太难，先不看。
*/

#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int maxc = 1000 + 1;

// original data  初始数据
int n, x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];

// discretization related  离散化
int nx, ny, nz;
int xs[maxn * 2], ys[maxn * 2], zs[maxn * 2];

// floodfill related 转化
const int dx[] = { 1,-1,0,0,0,0 };
const int dy[] = { 0,0,1,-1,0,0 };
const int dz[] = { 0,0,0,0,1,-1 };
int color[maxn * 2][maxn * 2][maxn * 2];

struct Cell 
{
	int x, y, z;
	Cell(int x = 0, int y = 0, int z = 0) :x(x), y(y), z(z) {}
	bool valid() const 
	{
		return x >= 0 && x < nx - 1 && y >= 0 && y < ny - 1 && z >= 0 && z < nz - 1;
	}
	bool solid() const 
	{
		return color[x][y][z] == 1; // solid
	}
	bool getVis() const 
	{
		return color[x][y][z] == 2; // visited
	}
	void setVis() const 
	{
		color[x][y][z] = 2;
	}
	Cell neighbor(int dir) const 
	{
		return Cell(x + dx[dir], y + dy[dir], z + dz[dir]);
	}
	int volume() const 
	{
		return (xs[x + 1] - xs[x])*(ys[y + 1] - ys[y])*(zs[z + 1] - zs[z]);
	}
	int area(int dir) const 
	{
		if (dx[dir] != 0) return (ys[y + 1] - ys[y])*(zs[z + 1] - zs[z]);
		else if (dy[dir] != 0) return (xs[x + 1] - xs[x])*(zs[z + 1] - zs[z]);
		return (xs[x + 1] - xs[x])*(ys[y + 1] - ys[y]);
	}
};

void discretize(int* x, int& n) 
{
	sort(x, x + n);
	n = unique(x, x + n) - x;
}

int ID(int* x, int n, int x0) 
{
	return lower_bound(x, x + n, x0) - x;
}

void floodfill(int& v, int& s) 
{
	v = 0;
	s = 0;
	Cell c;
	c.setVis();
	queue<Cell> q;
	q.push(c);
	while (!q.empty())
	{
		Cell c = q.front(); q.pop();
		v += c.volume();
		for (int i = 0; i < 6; i++) 
		{
			Cell c2 = c.neighbor(i);
			if (!c2.valid()) continue;
			if (c2.solid()) s += c.area(i);
			else if (!c2.getVis()) 
			{
				c2.setVis();
				q.push(c2);
			}
		}
	}
	v = maxc * maxc*maxc - v;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		nx = ny = nz = 2;
		xs[0] = ys[0] = zs[0] = 0;//暂时看不懂
		xs[1] = ys[1] = zs[1] = maxc;//
		scanf("%d", &n);
		for (int i = 0; i < n; i++) 
		{
			scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x1[i], &y1[i], &z1[i]);//初始数据
			x1[i] += x0[i]; y1[i] += y0[i]; z1[i] += z0[i];
			xs[nx++] = x0[i]; xs[nx++] = x1[i];
			ys[ny++] = y0[i]; ys[ny++] = y1[i];
			zs[nz++] = z0[i]; zs[nz++] = z1[i];//二次记录
		}
		discretize(xs, nx);
		discretize(ys, ny);
		discretize(zs, nz);//排序后去除重复元素（还是看不懂）

		// paint
		memset(color, 0, sizeof(color));
		for (int i = 0; i < n; i++) 
		{
			int X1 = ID(xs, nx, x0[i]), X2 = ID(xs, nx, x1[i]);
			int Y1 = ID(ys, ny, y0[i]), Y2 = ID(ys, ny, y1[i]);
			int Z1 = ID(zs, nz, z0[i]), Z2 = ID(zs, nz, z1[i]);//返回
			for (int X = X1; X < X2; X++)
				for (int Y = Y1; Y < Y2; Y++)
					for (int Z = Z1; Z < Z2; Z++)
						color[X][Y][Z] = 1;
		}

		int v, s;
		floodfill(v, s);
		printf("%d %d\n", s, v);
	}

	return 0;
}