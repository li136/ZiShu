//问题描述：编写函数，参数是两个非负整数n,m（m<=n<=25）。返回组合数c=(n!)/(m!*(n-m)!)



//例一（有问题）

//函数求n的阶乘
long long factorial(int n)
{
    long long m=1;
    for(int i=1;i<=n;i++)
        m*=i;
    return m;
}

//求组合数
long long C(int n,int m)
{
    return factorial(n)/(factorial(m)*factorial(n-m));
}
/*
错误原因：计算中间结果超出 long long int 范围  
*/



 

//例二
long long C(int n,int m)
{
    if(m<n-m)                  //这里的if语句巧妙的将组合数问题转化为两个循环
        m=n-m;                 //m=n-m保证了n!/(x)!中x为m和n-m的较大数
    long long ans=1;
    for(int i=m+1;i<=n;i++)
        ans*=i;
    for(int i=1;i<=n-m;i++)
        ans/=i;
}
//整合原来的两个函数，并简化过程，防止中间结果过大。