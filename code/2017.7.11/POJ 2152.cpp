#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=1001;
const int inf=2147483647;

class Edge
{
public:
    int v,w;
};

int n;
int W[maxN];
int D[maxN];
vector<Edge> E[maxN];
int Dist[maxN];
int F[maxN][maxN];
int Best[maxN];
queue<int> Q;

int read();
void dfs(int u,int father);

int main()
{
    int TT;
    TT=read();
    for (int ti=1;ti<=TT;ti++)
    {
        n=read();
        for (int i=1;i<=n;i++)//注意多组数据记得清空
            E[i].clear();
        for (int i=1;i<=n;i++)
            W[i]=read();
        for (int i=1;i<=n;i++)
            D[i]=read();
        for (int i=1;i<n;i++)
        {
            int x=read(),y=read(),w=read();
            E[x].push_back((Edge){y,w});
            E[y].push_back((Edge){x,w});
        }
        //cout<<"Read_end"<<endl;
        dfs(1,1);
        cout<<Best[1]<<endl;
    }
    return 0;
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
    while ((ch>='0')&&(ch<='9'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

void dfs(int u,int father)
{
    for (int i=0;i<E[u].size();i++)//首先把所有子节点的值算出来
    {
        int v=E[u][i].v;
        if (v==father)
            continue;
        dfs(v,u);
    }
    memset(Dist,-1,sizeof(Dist));//临时用bfs求出u到所有点的距离
    while (!Q.empty())
        Q.pop();
    Dist[u]=0;
    Q.push(u);
    do
    {
        int uu=Q.front();
        Q.pop();
        for (int i=0;i<E[uu].size();i++)
        {
            int v=E[uu][i].v;
            if (Dist[v]==-1)
            {
                Dist[v]=Dist[uu]+E[uu][i].w;
                Q.push(v);
            }
        }
    }
    while (!Q.empty());
    Best[u]=inf;//因为要求最小，所以初值为无穷大
    for (int build=1;build<=n;build++)
    {
        if (Dist[build]<=D[u])
        {
            F[u][build]=W[build];
            for (int i=0;i<E[u].size();i++)
            {
                int v=E[u][i].v;
                if (v==father)
                    continue;
                F[u][build]+=min(Best[v],F[v][build]-W[build]);//统计u的子节点v
            }
            Best[u]=min(Best[u],F[u][build]);//用刚计算出来的F[u][build]更新Best[u]
        }
        else//若build无法覆盖u，则置为无穷大
            F[u][build]=inf;
    }
    return;
}