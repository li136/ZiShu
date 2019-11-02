/*
 UVa 839
 问题描述：
 输入一个树状天平，根据力矩相等原则判断是否平衡。
 
 例·1：
 输入：
 1

 0 2 0 4
 0 3 0 1 
 1 1 1 1
 2 4 4 2 
 1 6 3 2 
输出“YES”or“NO”
*/

// 题意：输入一个树状天平，根据力矩相等原则判断是否平衡。采用递归方式输入，0表示中间结点
// 算法：在“建树”时直接读入并判断，并且无须把树保存下来
#include<iostream>
using namespace std;

// 输入一个子天平，返回子天平是否平衡，参数W修改为子天平的总重量
//solve函数用的也是先序遍历的方式，恰好和输入数据的顺序一样。
bool solve(int& W) //用引用修改参数。
{
	int W1, D1, W2, D2;
	bool b1 = true, b2 = true;
	cin >> W1 >> D1 >> W2 >> D2;
	if (!W1) b1 = solve(W1);
	if (!W2) b2 = solve(W2);
	W = W1 + W2;
	return b1 && b2 && (W1 * D1 == W2 * D2);
}

int main() 
{
	int T, W;
	cin >> T;
	while (T--) 
	{
		if (solve(W)) cout << "YES\n"; else cout << "NO\n";
		if (T) cout << "\n";
	}
	return 0;
}

