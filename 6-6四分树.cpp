/*
 UVa 297
 问题描述：
 四分树以右上，左上，左下，右下的顺序确定子结点的顺序。先序遍历，当进入子结点时，输入p
 结点纯黑时输入f，纯白输入e，黑白混杂输入p进入子结点。

 输入两个四分树，输出相加的黑色面积，有黑色相加为黑（黑色合并）。
*/

/*
 函数：
 memset()
*/

// 算法：先建树，然后统计
#include<cstdio>
#include<cstring>

const int len = 32;
const int maxn = 1024 + 10;
char s[maxn];
int buf[len][len], cnt;

// 把字符串s[p..]导出到以(r,c)为左上角，边长为w的缓冲区中
// 2 1
// 3 4
void draw(const char* s, int& p, int r, int c, int w) 
{
	char ch = s[p++];
	if (ch == 'p') 
	{
		draw(s, p, r, c + w / 2, w / 2); // 1
		draw(s, p, r, c, w / 2); // 2
		draw(s, p, r + w / 2, c, w / 2); // 3
		draw(s, p, r + w / 2, c + w / 2, w / 2); // 4
	}
	else if (ch == 'f')  // 画黑像素（白像素不画）
	{
		for (int i = r; i < r + w; i++)
			for (int j = c; j < c + w; j++)
				if (buf[i][j] == 0) { buf[i][j] = 1; cnt++; }
	}
}

int main() 
{
	int T;
	scanf_s("%d", &T);
	while (T--) 
	{
		memset(buf, 0, sizeof(buf));
		cnt = 0;
		for (int i = 0; i < 2; i++) 
		{
			scanf_s("%s", s, maxn);
			int p = 0;
			draw(s, p, 0, 0, len);
		}
		printf("There are %d black pixels.\n", cnt);
	}
	return 0;
}