/*
 UVa 699
 问题描述：
 给一个二叉树，每一个结点都有一个水平位置，左右子结点分别离父结点一个距离单位。
 从左到右输出每个单位的结点权值之和。
 先序递归方式依次输出权值。-1表示空树。
*/

/*
 函数：
 sizeof()求大小。
 memset()函数：将给定范围的数组赋值，这里要注意的是该函数是逐字节拷贝的，要用sizeof()函数。
*/

// 算法：在“建树”(递归)的同时计算，无须真正的把树保存下来

#include<cstring>
#include<iostream>
using namespace std;

const int maxn = 200;
int sum[maxn];

// 输入并统计一棵子树，树根水平位置为p
void build(int p) 
{
	int v;
	cin >> v;
	if (v == -1) return; // 空树
	sum[p] += v;
	build(p - 1);
	build(p + 1);
}

// 边读入边统计
bool init() 
{
	int v;
	cin >> v;
	if (v == -1) return false;

	memset(sum, 0, sizeof(sum));
	int pos = maxn / 2; // 树根的水平位置
	sum[pos] = v;
	build(pos - 1); // 左子树
	build(pos + 1); // 右子树
    return true;
}

int main() 
{
	int kase = 0;
	while (init()) 
	{
		int p = 0;
		while (sum[p] == 0) p++; // 找最左边的叶子

		// 开始输出。因为要避免行末多余空格，所以稍微麻烦一点
		cout << "Case " << ++kase << ":\n" << sum[p++];
		while (sum[p] != 0) 
		{
			cout << " " << sum[p];
			p++;
		}
		cout << "\n\n";
	}
	return 0;
}