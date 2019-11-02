/*
 UVa 122
 问题描述：
 给出每个结点的位置和值。按从上到下，从左到右的顺序输出结点的值。
*/

/*
 函数：
 strlen()函数,sscanf(),,clear(),size(),front()
 
 strchr()函数：例strchr(str, ',') 输入字符串str和一个char。输入这个char在字符串第一次出现的位置（指针）
 
 strcmp()函数：
strcmp函数是C/C++中基本的函数，它对两个字符串进行比较，然后返回比较结果，函数形式如下：
int strcmp(const char* str1, const char* str2);
其中str1和str2可以是字符串常量或者字符串变量，返回值为整形。返回结果如下规定：
① str1小于str2，返回负值或者-1（VC返回-1）；      
② str1等于str2，返回0；
③ str1大于str2，返回正值或者1（VC返回1）；
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int maxn = 256 + 10;

struct Node 
{
	bool have_value;
	int v;
	Node* left, *right;

	Node() :have_value(false), left(NULL), right(NULL) {}
};

Node* root;

Node* newnode() { return new Node(); }//new类时返回类的指针？？？？

bool failed;
void addnode(int v, char* s)
{
	int n = strlen(s);//这里的s是一个指针，但依然可以用strlen()函数。
	Node* u = root;//从根结点向下
	for (int i = 0; i < n; i++)
		if (s[i] == 'L')
		{
			if (u->left == NULL) u->left = newnode();
			u = u->left;
		}
		else if (s[i] == 'R')
		{
			if (u->right == NULL) u->right = newnode();
			u = u->right;
		}
	if (u->have_value) failed = true;//有重复结点
	u->v = v;	`
	u->have_value = true;
}

void remove_tree(Node* u)//将node u的left和right清空。delete空间。
{
	if (u == NULL) return;
	remove_tree(u->left);
	remove_tree(u->right);
	delete u;
}

char s[maxn];
bool read_input()
{
	failed = false;
	remove_tree(root);//清空root的left和right
	root = newnode();//new一个新类，将地址赋给root
	for (;;)
	{
		if (scanf("%s", s) != 1) return false;//读取到错误信息
		if (!strcmp(s, "()")) break;//出现结束输出标志,通过比较大小的方式判断是否相等
		int v;
		sscanf_s(&s[1], "%d", &v);//从字符串读取到编号赋值到v
		addnode(v, strchr(s, ',') + 1);
	}
	return true;
}

bool bfs(vector<int>& ans) //BFS层次遍历的关键函数
{
	queue<Node*> q;//做队列的意义
	ans.clear();
	q.push(root);
	while (!q.empty())
	{
		Node* u = q.front(); q.pop();
		if (!u->have_value) return false;
		ans.push_back(u->v);
		if (u->left != NULL) q.push(u->left);
		if (u->right != NULL) q.push(u->right);
	}
	return true;
}

int main() 
{
	vector<int> ans;
	while (read_input()) 
	{
		if (!bfs(ans)) failed = true;
		if (failed) printf("not complete\n");
		else 
		{
			//STL的size()  算法头文件的length()-万能  不知道哪里的strlen()-c字符串
			for (int i = 0; i < ans.size(); i++)
			{
				if (i != 0) printf(" ");
				printf("%d", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}