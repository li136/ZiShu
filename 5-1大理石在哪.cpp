/*
 问题描述；
 有N块大理石，每块写上一个非负整数，先从小到大排序
 然后回答Q个问题，每个问题问Xn是否存在，如果存在，请说出位子。


 例：
  4 1                                4为N，1为Q
  2 3 5 1                            
  5

  回答：
  5 found at 4
*/


/*
 问题用普通数组储存元素，用sort()函数排序
 使用函数：
     sort()函数排序
     lower_bound()查找大于或者等于x的第一个位置（输出指针）
                  如果没有则输出最后一个指针
*/

#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10000;

int main()
{
    int n,q,x,a[maxn],kase=0;
    while(scanf("%d%d",&n,&q)==2&&n)//先检查n,q是否被合法输入。然后检查n是否为0。
    {
        printf("CASE# %d:\n", ++kase)//用kase保存记录循环次数
        for(int i=0;i<n;i++)
            scanf("%d",&a[i])//记录N块大理石的数
        sort(a,a+n);//排序，输入数据为数组前后的两个指针
        while(q--)//循环Q个问题
        {
            scanf("%d",&x);
            int p=lower_bound(a,a+n,x)-a//用lower_bound()函数在已排序数组中寻找x的位置
            if(a[p]==x)
                printf("%d found st %d\n",x,p+1);
            else
                printf("%d not found\n",x);
        }
    }
    return 0;
}