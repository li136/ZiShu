/*
 UVa140 Bandwidth    并没有剪枝！！！！！！！！这是欺诈！！！

 给一个最多8个结点的无向图，
 把结点重排后对于图中每条边(u,v)，u和v在排列中的最大距离称为该排列的带宽。
 求带宽最小的排列.
 样例输入：
 A:FB;B:GC;D:GC;F:AGH;E:HD
 #
 输出：
 A B C F G D H E -&gt; 3
*/

#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 10;
int id[256], letter[maxn];

int main() 
{
	char input[1000];
	while (scanf("%s", input) == 1 && input[0] != '#') 
    {
		// 计算结点个数放在n中    字母编号放在id中   编号反向的字母索引放在letter中
		int n = 0;
		for (char ch = 'A'; ch <= 'Z'; ch++)
			if (strchr(input, ch) != NULL) //是否存在
            {
				id[ch] = n++; //出现了几种字母，并编号
				letter[id[ch]] = ch; //反向标记
			}

		// 处理输入
		int len = strlen(input), p = 0, q = 0;
		vector<int> u, v;
		for (;;) 
        {
			while (p < len && input[p] != ':') p++;
			if (p == len) break;
			while (q < len && input[q] != ';') q++;
			for (int i = p + 1; i < q; i++)
            {
				u.push_back(id[input[p - 1]]);//对应的头
				v.push_back(id[input[i]]);//对应的尾
			}
			p++; q++;
		}

		// 枚举全排列
		int P[maxn], bestP[maxn], pos[maxn], ans = n;
		for (int i = 0; i < n; i++) P[i] = i;
		do 
        {
			for (int i = 0; i < n; i++) pos[P[i]] = i; // 记录每个字母的位置，方便计算带宽
			int bandwidth = 0;
			for (int i = 0; i < u.size(); i++)
				bandwidth = max(bandwidth, abs(pos[u[i]] - pos[v[i]])); // 计算带宽
			if (bandwidth < ans) 
            {
				ans = bandwidth;
				memcpy(bestP, P, sizeof(P));
			}
		} while (next_permutation(P, P + n));

		// 输出
		for (int i = 0; i < n; i++) 
            printf("%c ", letter[bestP[i]]);
		printf("-> %d\n", ans);
	}
	return 0;
}