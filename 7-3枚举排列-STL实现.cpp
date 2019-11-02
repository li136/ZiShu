/*
用STL的next_permutation函数（algorithm头文件）枚举所有排列
输入正整数n和n个数。
输出所有排列
*/

#include<algorithm>
#include<cstdio>
using namespace std;

int main()
{
    int n,p[10];

    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);
    sort(p);

    do
    {
        for(int i=0;i<n;i++)
            printf("%d",p[i]);
    }while(next_permutation(p,p+n));

    return 0;
}