/*
Uva 11059

输入n个元素组成的序列S，你需要找出一个最大的连续子序列。
如果这个最大的乘积不是正数，输出0。
n=1~18   Si=-10~10
*/

#include<iostream>
using namespace std;

int main() 
{
	int S[20], kase = 0, n;
	while (cin >> n && n)
    {
		for (int i = 0; i < n; i++) cin >> S[i];
		long long ans = 0;
        
		for (int i = 0; i < n; i++) 
        {
			long long v = 1;
			for (int j = i; j < n; j++) 
            {
				v *= S[j];
				if (v > ans) ans = v;
			}
		}
		cout << "Case #" << ++kase << ": The maximum product is " << ans << ".\n\n";
	}
	return 0;
}