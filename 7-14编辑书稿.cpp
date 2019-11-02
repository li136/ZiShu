/*
UVa11212 Editing a Book
问题描述：
不断剪切粘贴将一段连续数字（无序排列）正序排列，求最短步数

样例输入：5 4 3 2 1
输出：   3
*/

// This is not very fast, but easy to understand
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 9;
int n, a[maxn];

bool is_sorted() 
{
	for (int i = 0; i < n - 1; i++)
		if (a[i] >= a[i + 1]) return false;
	return true;
}

// the number of integers with incorrect successor
int h() 
{
	int cnt = 0;
	for (int i = 0; i < n - 1; i++)
		if (a[i] + 1 != a[i + 1]) cnt++;
	if (a[n - 1] != n) cnt++;
	return cnt;
}

bool dfs(int d, int maxd)
{
	if (d * 3 + h() > maxd * 3) return false;// 乐观估价函数
	if (is_sorted()) return true;  //判定是否有序

	int b[maxn], olda[maxn];
	memcpy(olda, a, sizeof(a));
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) 
        {
			// cut
			int cnt = 0;
			for (int k = 0; k < n; k++)
				if (k < i || k > j) b[cnt++] = a[k];//剪切1~i和j~n这两段到b数组

			// insert before position k
			for (int k = 0; k <= cnt; k++) 
            {
				int cnt2 = 0;
				for (int p = 0; p < k; p++) a[cnt2++] = b[p];
				for (int p = i; p <= j; p++) a[cnt2++] = olda[p];
				for (int p = k; p < cnt; p++) a[cnt2++] = b[p];

				if (dfs(d + 1, maxd)) return true;
				memcpy(a, olda, sizeof(a)); 
			}
		}
	return false;
}

int solve() 
{
	if (is_sorted()) return 0;
	int max_ans = 5; // after experiments, we found ans <= 5 for n <= 9
	for (int maxd = 1; maxd < max_ans; maxd++)
		if (dfs(0, maxd)) return maxd;
	return max_ans;
}

int main() 
{
	int kase = 0;
	while (scanf("%d", &n) == 1 && n) 
    {
		for (int i = 0; i < n; i++) 
            scanf("%d", &a[i]);
		printf("Case %d: %d\n", ++kase, solve());
	}
	return 0;
}