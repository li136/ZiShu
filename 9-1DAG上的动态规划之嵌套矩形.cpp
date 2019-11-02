/* DAG上的动态规划之嵌套矩形 */
#include <cstdio>
#include <cstring>

const int maxn = 1005;
int n, G[maxn][maxn];
int a[maxn], b[maxn];
int dp[maxn];

void swap(int &x, int &y){
    x ^= y;
    y ^= x;
    x ^= y;
}

//将x和y的最大值存在x中
inline void CMAX(int& x, int y)
{
    if (y > x)
        x = y;
}

/* 采用记忆化搜索 求从s能到达的最长路径 */
int DP(int s)
{
    int& ans = dp[s];
    if (ans > 0)
        //记忆化搜索,避免重复计算
        return ans;
    ans = 1;
    for (int j = 1; j <= n; ++j)
        if (G[s][j])
            CMAX(ans, DP(j) + 1);//sj有边 利用子问题dp[j]+1更新最大值
    return ans;
}

void print_ans(int i){
    printf("%d ", i);
    for (int j = 1; j <= n; ++j)
        if (G[i][j] && dp[j] + 1 == dp[i])//路径由大到小递减。有点像之前的逆BFS
        {
            print_ans(j);
            break;
        }
}

int main()
{
    while (scanf("%d", &n) == 1)
    {
        //n个矩形
        for (int i = 1; i <= n; ++i)
        {
            //默认a存长,b存宽(a > b)
            scanf("%d%d", a + i, b + i);
            if (a[i] < b[i])
                swap(a[i], b[i]);
        }
        /*
            建图 G[i][j]为1表示矩形i可以嵌套在矩形j中
            那么原问题便转化为求DAG上的最长路径
            
            定义状态dp[i]表示从结点i出发可以到达的最长路径
            则 dp[i] = max(dp[j] + 1), 其中 G[i][j]=1，
        */
        memset(G, 0, sizeof G);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (a[i] < a[j] && b[i] < b[j])//矩形i的长和宽都小于矩形j的长和宽
                    G[i][j] = 1; //可以嵌套,则有边
        
        memset(dp, 0, sizeof dp);
        int ans = 0;
        int best;
        for (int i = 1; i <= n; ++i)
        {
            if (DP(i) > ans)
            {
                ans = dp[i];//更新最长路径
                best = i;
            }
        }//for(i)
        printf("ans = %d\n", ans);
        print_ans(best);
        printf("\n");
    }
    return 0;
}