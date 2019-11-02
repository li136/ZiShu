/*
丑数是指不能被2，3，5以外的素数整除的数。
1，2，3，4，5，6，8，9，10，12，15
求第1500个丑数

主要用了优先队列的存取机制。
另外用了set的判重，防止重复元素放入优先队列中
*/

#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;

typedef long long LL;
const int coeff[3]={2,3,5};

int main()
{
    priority_queue <LL ,vector<LL> ,greater<LL> > pq;//小根堆的优先队列定义，大根堆只需要int（LL）就可以了
    set <LL> s;
    pq.push(1);
    s.insert(1);

    for(int i=1; ;i++)
    {
        LL x=pq.top();pq.pop();
        if(i==1500)
        {
            cout<<"The 1500'th ugly number is "<<x<<".\n";
            break;
        }
        for(int j=0;j<3;j++)
        {
            LL x2=x*coeff[j];
            if(!s.count(x2))
            { s.insert(x2);pq.push(x2); }
        }
    }
    
    return 0;
}