/*
UVA1354 天平难题 Mobile Computing

给出房间宽度r和s个吊坠的重量wi。设计一个尽量宽（不超过r)的天平，挂着所有挂坠。 
天平由一些长度为1的木棍组成。木棍的每一端要么挂一个挂坠，要么挂另外一个木棍。
设n和m分别是两端挂的总重量，a和b为两端长度，要让天平平衡，必须满足na=mb。

*/

#include<cstdio>
#include<cstring>   
#include<vector>
using namespace std;

struct Tree 
{
	double L, R; // distance from the root to the leftmost/rightmost point
	Tree() :L(0), R(0) {}
};

const int maxn = 6;

int n, vis[1 << maxn];
double r, w[maxn], sum[1 << maxn];
vector<Tree> tree[1 << maxn];

void dfs(int subset) 
{
	if (vis[subset]) return;
	vis[subset] = true;

	bool have_children = false;//初始化
	for (int left = (subset - 1)&subset; left; left = (left - 1)&subset) 
    {//遍历每一种情况，取subset的子集所以要取交集，从上一个的集合再取交集可以提高效率
		have_children = true;//进入循环表明有子集

		int right = subset ^ left;//得到差集
		double d1 = sum[right] / sum[subset];//公示推导出来的
		double d2 = sum[left] / sum[subset];

		dfs(left); dfs(right);

		for (int i = 0; i < tree[left].size(); i++)
			for (int j = 0; j < tree[right].size(); j++) 
            {
				Tree t;
				t.L = max(tree[left][i].L + d1, tree[right][j].L - d2);//判断两个支路哪个更长。
				t.R = max(tree[right][j].R + d2, tree[left][i].R - d1);
				if (t.L + t.R < r) tree[subset].push_back(t);
			}
	}

	if (!have_children) tree[subset].push_back(Tree());
}

int main() 
{
	int T;
	scanf("%d", &T);
	while (T--) 
    {
		scanf("%lf%d", &r, &n);
		for (int i = 0; i < n; i++) scanf("%lf", &w[i]);
		for (int i = 0; i < (1 << n); i++) 
        {//遍历每一种可能
			sum[i] = 0;
			tree[i].clear();
			for (int j = 0; j < n; j++)
				if (i & (1 << j)) sum[i] += w[j];//把这个集合中的质量都加起来，包含第j个质量的集合。
		}

		int root = (1 << n) - 1;//全部都是1
		memset(vis, 0, sizeof(vis));
		dfs(root);

		double ans = -1;
		for (int i = 0; i < tree[root].size(); i++)
			ans = max(ans, tree[root][i].L + tree[root][i].R);//找到最大值
		printf("%.10lf\n", ans);
	}
	return 0;
}
