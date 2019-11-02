/*
n(n<20)个人围成一圈，逆时针编号1~n。
两个官员A，B。A，B分别选一个数k,m。
A从1开始逆时针数，B从n顺时针数。选中的人离开。分别输出离开人的标号（各不相同）（先A再B）（若A，B选中同一人，输出一次）
*/

#include<cstdio>

const int maxn=25；
int n,k,m,a[maxn];

//输出终点位置
int go(int p,int d,int t)//p为起始位置，d为步长，t为走几步。
{
    while(t--)
    {
        do
        {
            p=(p+d+n-1)%n+1;
        }while(a[p]==0);
    }
    return p;
}

int main()
{
    while(scanf_s("%d%d%d",&n,&k,&m)==3&&n)
    {
        for(int i=1;i<=n;i++)
        a[i]=i;
        int left=n;
        int p1=n,p2=1;
        while(left)
        {
            p1=go(p1,1,k);
            p2=go(p2,-1,m);
            printf("%3d",p1);
            left--;
            if(p2!=p1)
            {
                printf("%3d",p2);left--;
            }
            a[p1]=a[p2]=0;
            if(left)
            printf(",");
        }
        printf("\n");
    }
    return 0;
}