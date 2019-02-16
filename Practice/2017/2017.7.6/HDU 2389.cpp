#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=4000;
const int inf=2147483647;

int n,m;
int Time;//距离下雨的时间
int Dist;//下面这些变量的意义在上文已经讲过啦
vector<int> E[maxN];
int Match_x[maxN];
int Match_y[maxN];
bool vis[maxN];
int Deep_x[maxN];
int Deep_y[maxN];
int X[maxN];//人的X坐标
int Y[maxN];
int Speed[maxN];//人的速度

int read();
bool Judge(int u,int v,int num);
bool bfs();
bool Hungary(int u);

int main()
{
    int T;
    T=read();
    for (int ti=1;ti<=T;ti++)
    {
        Time=read();
        m=read();
        for (int i=1;i<=m;i++)
            E[i].clear();
        for (int i=1;i<=m;i++)
        {
            X[i]=read();
            Y[i]=read();
            Speed[i]=read();
        }
        n=read();
        for (int i=1;i<=n;i++)
        {
            int x,y;
            x=read();
            y=read();
            for (int j=1;j<=m;j++)
                if (Judge(x,y,j))
                {
                    E[j].push_back(i);
                }
        }
        int Ans=0;
        mem(Match_x,-1);
        mem(Match_y,-1);
        while (bfs())//HK算法
        {
            mem(vis,0);
            for (int i=1;i<=m;i++)
                if (Match_x[i]==-1)
                    if (Hungary(i))
                        Ans++;
        }
        printf("Scenario #%d:\n%d\n\n",ti,Ans);
    }
    return 0;
}

int read()//读入优化
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch<'0')||(ch>'9'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

bool Judge(int u,int v,int num)//判断某个人是否可以跑到某把伞
{
    long long Dist=(long long)((X[num]-u))*(X[num]-u)+(long long)((Y[num]-v))*(Y[num]-v);
    long long D=(long long)(Time)*Speed[num];
    if (D*D>=Dist)
        return 1;
    return 0;
}

bool bfs()
{
    queue<int> Q;//bfs要用的队列
    while (!Q.empty())
        Q.pop();
    Dist=inf;//先置为inf
    mem(Deep_x,-1);//先置为-1，表示还未经过
    mem(Deep_y,-1);
    for (int i=1;i<=m;i++)
        if (Match_x[i]==-1)//若人i还未匹配，则将其加入队列（因为增广路的开始点是未匹配点）
        {
            Deep_x[i]=0;
            Q.push(i);
        }
    while (!Q.empty())//因为有可能所有人都已经匹配，所以要把while判断写前面，以免出现RE
    {
        int u=Q.front();
        Q.pop();
        if (Deep_x[u]>Dist)//若发现当前选出的人u的深度已经大于能形成增广路的最大深度了，直接退出。这是一个很好的剪枝
            break;
        for (int i=0;i<E[u].size();i++)
        {
            int v=E[u][i];//选择伞v
            if (Deep_y[v]==-1)//若伞v在这一次bfs中还未走过
            {
                Deep_y[v]=Deep_x[u]+1;//首先更新伞v的深度，同时表示已经处理过伞v了
                if (Match_y[v]==-1)//当伞v还未匹配时，说明找到了一条增广路，这时更新最长增广路的值Dist。因为是bfs，所以可以保证越在后面出来的Deep值越大，所以不用加max
                {
                    Dist=Deep_y[v];
                }
                else//如果伞v已经匹配，则处理其对应的匹配的人，并将这个人加入队列
                {
                    Deep_x[Match_y[v]]=Deep_y[v]+1;
                    Q.push(Match_y[v]);
                }
            }
        }
    }
    //cout<<"Dist "<<Dist<<endl;
    if (Dist==inf)//这表示没有增广路了，说明算法执行完毕，返回0
        return 0;
    return 1;
}

bool Hungary(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if ((vis[v]==0)&&(Deep_x[u]+1==Deep_y[v]))//注意，这里用到了bfs计算出来的Deep数组，这可以用来判断当前选的伞v是否是我们在dfs中选的那条增广路，有效剪枝
        {
            vis[v]=1;
            if ((Match_y[v]!=-1)&&(Deep_y[v]==Dist))//若发现当前伞v的Deep已经和最大增广路长度一样，并且伞v已匹配，那么再递归向下找是无意义的，直接continue
                continue;
            if ((Match_y[v]==-1)||(Hungary(Match_y[v])))
            {
                Match_x[u]=v;//注意，因为添加了人对应匹配的伞这个变量，所以也要更新（这在之前的匈牙利中是没有的）
                Match_y[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
/* 匈牙利算法，TLE
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=4000;
const int inf=2147483647;

int n,m;
vector<int> E[maxN];
bool vis[maxN];
int Match[maxN];
int GuestX[maxN];
int GuestY[maxN];
int Speed[maxN];

int read();
bool Hungary(int u);

int main()
{
    int T;
    int Time;
    cin>>T;
    for (int ti=1;ti<=T;ti++)
    {
        cin>>Time;
        cin>>m;
        for (int i=1;i<=m;i++)
            E[i].clear();
        for (int i=1;i<=m;i++)
        {
            GuestX[i]=read();
            GuestY[i]=read();
            Speed[i]=read();
            Speed[i]=Speed[i]*Time;
        }
        int x,y;
        cin>>n;
        for (int i=1;i<=n;i++)
        {
            x=read();
            y=read();
            for (int j=1;j<=m;j++)
            {
                int Dist=(x-GuestX[j])*(x-GuestX[j])+(y-GuestY[j])*(y-GuestY[j]);
                if (Speed[i]*Speed[i]>=Dist)
                    E[j].push_back(i);
            }
        }
        int Ans=0;
        memset(Match,-1,sizeof(Match));
        for (int i=1;i<=m;i++)
        {
            memset(vis,0,sizeof(vis));
            if (Hungary(i))
            {
                Ans++;
            }
        }
        printf("Scenario #%d:\n%d\n\n",ti,Ans);
        //cout<<Ans<<endl;
    }
}

int read()
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch<'0')||(ch>'9'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

bool Hungary(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1)||(Hungary(Match[v])))
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
*/