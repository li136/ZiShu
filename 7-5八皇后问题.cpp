#include<cstdio>
#include<queue>
#include<iostream>
#include <utility>
#include <algorithm>
#include<vector>
using namespace std;

int C[10];//暂时记录每行的皇后位置
const int n = 8;//皇后总数

char P[8][8]; //记录棋盘是否可以落
int N = 1;

void ewq(int i, int x, int y)//在xy的为周围加i
{
	for (int j = 0; j < n; j++)
	{
		P[x][j]+=i;
		P[j][y]+=i; 
		if (x-y+j>=0&& n > x - y + j)
		{
			P[x - y + j][j]+=i;
		}
		if (x+y-j >= 0&& n > x+y-j)
		{
			P[x+y-j][j]+=i;
		}
	}
	P[x][y] -= 3*i;
}

void pri()//打印解
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", ((C[i] == j) ? 1 : 0));
		printf("\n");
	} 
	printf("\n");
}

void pri_1()//第二种打印
{
	printf("No. %d\n", N++);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", ((C[j] == i) ? 1 : 0));
		printf("\n");
	}
}

void qwe(int cur)
{
	for (int i = 0; i < n; i++)
	{
		if (!P[cur][i])//有位置
		{
			C[cur] = i;//标记位置
			if (cur == n - 1)
			{
				pri_1();
                continue;
			}
			ewq(1, cur, i);//写名字
			qwe(cur + 1);
			ewq(-1, cur, i);//取消名字
		}
	}
}


int main()
{
	memset(P, 0, sizeof(P));
	qwe(0);
	return 0;
}