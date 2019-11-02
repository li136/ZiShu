/*
    问题描述：循环输入数字（没什么意义的数字）和两个字符串
    如果第一个字符串的单词在第二个
    无聊的代码
*/

#include<iostream>
#include<cstdio>
#include<cstring>
constexpr auto maxn = 100;
using namespace std;
int Left, chance;
char s[maxn], s2[maxn];
int win, lose;

void guess(char ch)
{
	int bad = 1,n=strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] == ch)
		{
			Left--; s[i] = ' '; bad = 0;//用空格改变字符作为标记！！！！！！！！
		}
	if (bad)
		--chance;
	if (!chance)
		lose = 1;
	if (!Left)
		win = 1;
}

int main()
{
	int rnd;
	while (scanf_s("%d", &rnd) == 1 && rnd != -1)//可以借鉴！！！！！！！！
	{
		scanf_s("%s%s", s, 100, s2, 100);
		printf("Round %d\n", rnd);
		win = lose = 0;
		Left = strlen(s);
		chance = 7;
		for (int i = 0; i < strlen(s2); i++)
		{
			guess(s2[i]);
			if (win || lose)
				break;
		}
		//输出结果
		if (win)
			printf("you win\n");
		else if (lose)
			printf("you lose\n");
		else
			printf("you chickened out\n");
	}
	return 0;
}