//UVA 12563
//劲爆金曲

#include<bits/stdc++.h>//万能头文件，蒟蒻值得拥有
using namespace std;
int n,t;
int f[100000];
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)//有多组数据，这个坑别跳进去了
    {
        int m;
        memset(f,0x8f,sizeof(f));//这也是一个坑啊
        scanf("%d%d",&m,&t);
        f[0]=0;
        int hh;
        for (int j=1;j<=m;j++)
        {
            scanf("%d",&hh);
            for(int k=t-1;k>=hh;k--)
            {
                 f[k]=max(f[k],f[k-hh]+1);//转换方程：看看是否有f[i]的更优，更大值，如果有就替换
            }
        }
        int ans;
        for(int j=ans=t-1;j>=0;j--)//这里的j=ans=t-1可以当作是j=t-1;ans=t-1;只是为了偷懒而已
            if(f[j]>f[ans]) ans=j;

        printf("Case %d: %d %d\n",i,f[ans]+1,ans+678);//按照题目要求来输出
    }
    return 0;
}