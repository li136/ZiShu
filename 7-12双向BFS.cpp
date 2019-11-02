
#include<cstdio>
#include<cstring>
#include<cctype>
#include<list>
#include<algorithm>
using namespace std;
int w,h,n;
char pic[20][20];///输入
int num[20][20];///输入中的位置->图中节点的编号
int connect[200][200];///邻接表
int all;///图中节点的数量
 
int start[4];///起始状态
int goal[4];///目标状
 
int que_fro[1000000][4], que_back[1000000][4];///BFS队列
int vis_fro[200][200][200], vis_back[200][200][200];///标记数组
 
bool bfs_fro(const int &_step, int &fro, int &rear)
{
    while(fro < rear)
        int &step = que_fro[fro][0],&a =que_fro[fro][1], &b=que_fro[fro][2],&c=que_fro[fro][3];
        if(step>_step) break;
        if(vis_back[a][b][c]) return true;
 
        for(int i=0,t1;i<=connect[a][0];++i)
        {
            t1=(i==0?a:connect[a][i]);
            for(int j=0,t2; j<=connect[b][0];++j)
            {
                t2=(j==0?b:connect[b][j]);
                for(int k=0,t3;k<=connect[c][0];k++)
                {
                    t3=(k==0?c:connect[c][k]);
                    //判断冲突----
                    if((t1&&t2&&t1==t2)||(t1&&t3&&t1==t3)||(t2&&t3&&t2==t3)) continue;///不能对穿
                    if((t1&&t2&&t1==b&&t2==a)) continue;///t1,t2不能对穿
                    if((t1&&t3&&t1==c&&t3==a)) continue;///t1,t3不能对穿
                    if((t2&&t3&&t2==c&&t3==b)) continue;///t2,t3不能对穿
                    ///------------
                    if(!vis_fro[t1][t2][t3])
                    {
                        vis_fro[t1][t2][t3]=1;
                        que_fro[rear][0]=step+1;
                        que_fro[rear][1]=t1;
                        que_fro[rear][2]=t2;
                        que_fro[rear][3]=t3;
                        ++rear;
                    }
                }
            }
        }
        ++fro;
    }
    return false;
}
bool bfs_back(const int &_step, int &fro, int &rear)
{
    while(fro < rear)
    {
        int &step = que_back[fro][0],&a =que_back[fro][1], &b=que_back[fro][2],&c=que_back[fro][3];
        if(step>_step) break;
        if(vis_fro[a][b][c]) return true;
 
        for(int i=0,t1;i<=connect[a][0];++i)
        {
            t1=(i==0?a:connect[a][i]);
            for(int j=0,t2; j<=connect[b][0];++j)
            {
                t2=(j==0?b:connect[b][j]);
                for(int k=0,t3;k<=connect[c][0];k++)
                {
                    t3=(k==0?c:connect[c][k]);
                    //判断冲突----
                    if((t1&&t2&&t1==t2)||(t1&&t3&&t1==t3)||(t2&&t3&&t2==t3)) continue;///不能对穿
                    if((t1&&t2&&t1==b&&t2==a)) continue;///t1,t2不能对穿
                    if((t1&&t3&&t1==c&&t3==a)) continue;///t1,t3不能对穿
                    if((t2&&t3&&t2==c&&t3==b)) continue;///t2,t3不能对穿
                    ///------------
                    if(!vis_back[t1][t2][t3])
                    {
                        vis_back[t1][t2][t3]=1;
                        que_back[rear][0]=step+1;
                        que_back[rear][1]=t1;
                        que_back[rear][2]=t2;
                        que_back[rear][3]=t3;
                        ++rear;
                    }
                }
            }
        }
        ++fro;
    }
    return false;
}
int bfs()
{
    //初始化
    memset(vis_fro,0,sizeof(vis_fro)), memset(vis_back,0,sizeof(vis_back));
    int fro_fro(0),fro_back(0), rear_fro(1), rear_back(1);
    vis_fro[start[1]][start[2]][start[3]]=true, vis_back[goal[1]][goal[2]][goal[3]]=true;
    int step_fro = 0, step_back=0;
    que_fro[0][0]=start[0],que_fro[0][1]=start[1],que_fro[0][2]=start[2],que_fro[0][3]=start[3];
    que_back[0][0]=goal[0],que_back[0][1]=goal[1],que_back[0][2]=goal[2],que_back[0][3]=goal[3];
    ///双向BFS搜索
    while((fro_fro < rear_fro) || (fro_back < rear_back)){
        ///从前向后搜一层
        if(bfs_fro(step_fro, fro_fro, rear_fro)) return step_fro+step_back;
        else step_fro++;
        ///从后向前搜一层
        if(bfs_back(step_back,fro_back,rear_back)) return step_fro + step_back;
        else step_back++;
    }
    return -1;
}
int main()
{
    while(scanf("%d%d%d",&w,&h,&n)&&w&&h&&n){
        ///读取输入
        gets(pic[0]);
        for(int i=0;i!=h;i++) gets(pic[i]);
        ///--------
        ///根据输入初始化建立图
        memset(connect,0,sizeof(connect));
        all=0;
        ///获得编号
        for(int i=0;i!=h;i++) for(int j=0;j!=w;j++){
            if(pic[i][j]!='#') num[i][j] = ++all;
            else num[i][j]=0;
        }
        ///建立图
        for(int i=0;i!=h;i++) for(int j=0;j!=w;j++) if(num[i][j]){
            int &pos = num[i][j];
            if(num[i+1][j]) connect[pos][++connect[pos][0]]=num[i+1][j];
            if(num[i-1][j]) connect[pos][++connect[pos][0]]=num[i-1][j];
            if(num[i][j+1]) connect[pos][++connect[pos][0]]=num[i][j+1];
            if(num[i][j-1]) connect[pos][++connect[pos][0]]=num[i][j-1];
        }
        ///----------
        ///寻找初始状态和目标状态（测了一下字母范围只在abc之间）
        ///初始化
        start[0]=start[1]=start[2]=start[3]=0;
        goal[0]=goal[1]=goal[2]=goal[3]=0;
        ///寻找初始状态
        for(int i=0;i!=h;i++) for(int j=0;j!=w;j++) if(islower(pic[i][j])){
            if(pic[i][j]=='a') start[1]=num[i][j];
            if(pic[i][j]=='b') start[2]=num[i][j];
            if(pic[i][j]=='c') start[3]=num[i][j];
        }
        ///寻找目标状态
        for(int i=0;i!=h;i++) for(int j=0;j!=w;++j) if(isupper(pic[i][j])){
            if(pic[i][j]=='A') goal[1]=num[i][j];
            if(pic[i][j]=='B') goal[2]=num[i][j];
            if(pic[i][j]=='C') goal[3]=num[i][j];
        }
        printf("%d\n",bfs());
    }
}