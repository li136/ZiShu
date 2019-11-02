//问题描述：参数为正整数n。如果为素数返回1，否则返回0


//例一（有问题）
int is_prime(int n)
{
    for(int i=2;i*i<=n;i++)// i*i结果可能过大
        if(n%i==0)
            return 0;
    return 1;
}


//例二
int is_prime(int n)
{
    if(n<=1)
        return 0;
    int m=floor(sqrt(n)+0.5);//将判定值该为n的根号并四舍五入。  
    for(int i=2;i<=m;i++)
        if(n%i==0)
            return 0;
    return 1;
}