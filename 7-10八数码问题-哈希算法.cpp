/*
问题描述；
八数码问题，编号1~8的八个正方形滑块摆成3行3列。
给定初始局面和目标局面，求移动的最少步数，不能输出-1

样例；
输入：
2 6 4 1 3 7 0 5 8
8 1 5 7 3 6 4 0 2
输出:
31
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<iostream>
#include <utility>
#include <algorithm>  
#include<vector>
using namespace std;

typedef int State[9];
const int maxstate = 1000000;
State st[maxstate], goal;
int dist[maxstate];
//如果需要打印方案，添加一个‘父亲编号’数组  int fa[maxstate]

const int dx[] = { -1,1,0,0 };
const int dy[] = { 0,0,-1,1 };

//哈希技术实现
const int hashsize = 1000003;
int head[hashsize], Next[maxstate];

void init_lookup_table()
{
	memset(head, 0, sizeof(head));
}

int Hash(State& s)
{
	int v = 0;
	for (int i = 0; i < 9; i++)
		v = v * 10 + s[i];//把九个数合成为9位数
	return v % hashsize;  //确保hash函数值是不超过hash表大小的非负整数
}

int try_to_insert(int s)
{
	int h = Hash(st[s]);
	int u = head[h];  //从表头开始查找链表
	while (u)
	{
		if (memcmp(st[u], st[s], sizeof(st[s])) == 0)	return 0;  //找到了，插入失败
		u = Next[u];      //顺着链表继续找
	}
	Next[s] = head[h];  //插入到链表中
	head[h] = s;
	return  1;
}

int bfs()
{
	init_lookup_table();  //初始化查找表
	int front = 1, rear = 2;  //不使用下标0，因为0被看作“不存在”
	while (front < rear)
	{
		State& s = st[front];  //用引用简化代码
		if (memcmp(goal, s, sizeof(s)) == 0)  //找到目标状态，成功返回
			return front;
		int z;
		for (z = 0; z < 9; z++)  //确定'0'的位置
			if (!s[z])	break;  //获取行列编号（0~2）
		int x = z / 3, y = z % 3;
		for (int d = 0; d < 4; d++)
		{
			int newx = x + dx[d];
			int newy = y + dy[d];
			int newz = newx * 3 + newy;
			if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3)  //如果移动合法
			{
				State& t = st[rear];//在st中记录所有的状态
				memcpy(&t, &s, sizeof(s));  //拓展新节点
				t[newz] = s[z];
				t[z] = s[newz];
				dist[rear] = dist[front] + 1;  //更新新节点的距离值
				if(try_to_insert(rear))	rear++;  //如果成功插入查找表，修改队尾指针
			}
		}
		front++;    //拓展完毕后再修改队首指针
	}
	return 0;    //失败
}

int main()
{
	for (int i = 0; i < 9; i++)	scanf("%d", &st[1][i]);  //起始状态
	for (int i = 0; i < 9; i++)	scanf("%d", &goal[i]);  //目标状态

	int ans = bfs();                     //返回目标状态的下标

	if (ans > 0)	printf("%d\n", dist[ans]);
	else	printf("-1\n");

	return 0;
}