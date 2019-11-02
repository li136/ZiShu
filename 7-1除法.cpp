/*
Uva 725
问题描述：
输入正整数n，按从小到大的顺序输出所有形如abcde / fghij = n的表达式，
其中a~j恰好为数字0~9的一个排列，可以有前导零，n=2~79
样例输入：
62
输出：
79546 / 01283 = 62
94736 / 01528 = 62
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() 
{
	int n, kase = 0;
	char buf[99];

	while (scanf("%d", &n) == 1 && n) 
    {
		int cnt = 0;//统计解个数
		if (kase++) printf("\n");//kase负责输出\n

		for (int fghij = 1234; ; fghij++) 
        {
			int abcde = fghij * n;

			//sprintf函数值大于5位数时按原来输出。返回字符串长度
			if (sprintf(buf, "%05d%05d", abcde, fghij > 10) break;//结果大于10位数时，退出

			sort(buf, buf + 10);//排序后判断是否为0~9
			bool ok = true;
			for (int i = 0; i < 10; i++)
				if (buf[i] != '0' + i) ok = false;

			if (ok) 
            {
				cnt++;
				printf("%05d / %05d = %d\n", abcde, fghij, n);
			}
		}

		if (!cnt) printf("There are no solutions for %d.\n", n);
	}
	return 0;
}