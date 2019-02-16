#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxN=1100;
const int maxM=103001*10;
const int inf=2147483647;

class Edge
{
public:
    int u,v,cost,flow;
};

int n,m;
int st,ed;
int cnt;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[3][maxN];
int Q[maxM];
bool inqueue[maxN];
int cur[maxN];
int depth[maxN];

void Add_Edge(int u,int v,int cost,int flow);
void spfa1();
void spfa2();
bool bfs();
int dfs(int u,int flow);

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        cnt=-1;
        memset(Head,-1,sizeof(Head));
        scanf("%d%d",&n,&m);
        for (int i=1;i<=m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            Add_Edge(u,v,w,1);
        }
        scanf("%d%d",&st,&ed);
        spfa1();
        spfa2();
        /*
        for (int i=1;i<=n;i++)
            cout<<Dist[1][i]<<" ";
        cout<<endl;
        for (int i=1;i<=n;i++)
            cout<<Dist[2][i]<<' ';
        cout<<endl;
        //*/
        int Ans=0;
        while (bfs())
        {
            for (int i=1;i<=n;i++)
                cur[i]=Head[i];
            while (dfs(st,inf))
                Ans++;
        }
        printf("%d\n",Ans);
    }
    return 0;
}

void Add_Edge(int u,int v,int cost,int flow)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    E[cnt].u=u;
    E[cnt].v=v;
    E[cnt].cost=cost;
    E[cnt].flow=flow;

    cnt++;
    Next[cnt]=Head[v];
    Head[v]=cnt;
    E[cnt].u=v;
    E[cnt].v=u;
    E[cnt].cost=-cost;
    E[cnt].flow=0;
    return;
}

void spfa1()
{
    memset(Dist[1],127,sizeof(Dist[1]));
    memset(inqueue,0,sizeof(inqueue));
    int h=1,t=0;
    Q[1]=st;
    Dist[1][st]=0;
    inqueue[st]=1;
    do
    {
        t++;
        int u=Q[t];
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            if ((E[i].flow>0)&&(E[i].cost+Dist[1][u]<Dist[1][v]))
            {
                Dist[1][v]=Dist[1][u]+E[i].cost;
                if (inqueue[v]==0)
                {
                    h++;
                    Q[h]=v;
                    inqueue[v]=1;
                }
            }
        }
        inqueue[u]=0;
    }
    while (t!=h);
    return;
}

void spfa2()
{
    memset(Dist[2],127,sizeof(Dist[2]));
    memset(inqueue,0,sizeof(inqueue));
    int h=1,t=0;
    Q[1]=ed;
    inqueue[ed]=1;
    Dist[2][ed]=0;
    do
    {
        t++;
        int u=Q[t];
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            if ((E[i].cost<0)&&(Dist[2][u]-E[i].cost<Dist[2][v]))
            {
                Dist[2][v]=Dist[2][u]-E[i].cost;
                if(inqueue[v]==0)
                {
                    h++;
                    Q[h]=v;
                    inqueue[v]=1;
                }
            }
        }
        inqueue[u]=0;
    }
    while (t!=h);
    return;
}

bool bfs()
{
    memset(depth,-1,sizeof(depth));
    int h=1,t=0;
    Q[1]=st;
    depth[st]=1;
    do
    {
        t++;
        int u=Q[t];
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            if ((E[i].flow>0)&&(depth[v]==-1)&&(Dist[1][u]+E[i].cost+Dist[2][v]==Dist[1][ed]))
            {
                depth[v]=depth[u]+1;
                h++;
                Q[h]=v;
            }
        }
    }
    while (t!=h);
    if (depth[ed]==-1)
        return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==ed)
        return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if ((depth[v]==depth[u]+1)&&(E[i].flow>0)&&(Dist[1][u]+E[i].cost+Dist[2][v]==Dist[1][ed]))
        {
            int di=dfs(v,min(flow,E[i].flow));
            if (di>0)
            {
                E[i].flow-=di;
                E[i^1].flow+=di;
                return di;
            }
        }
    }
    return 0;
}
