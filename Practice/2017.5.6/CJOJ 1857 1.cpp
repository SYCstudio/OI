#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=201;
const int maxM=2701;
const int inf=2147483647;

int n,m;
int Ecnt=0;
int First[maxN];
int Next[maxM];
int Last[maxN];
int W[maxM];
int V[maxM];
int Dist[maxN];
int Tot[maxN];
bool vis[maxN];

void init();
void Add_Edge(int u,int v,int w);
bool check(int x);
bool spfa();

int main()
{
    while (cin>>n>>m)
    {
        int u,v,w;
        int Wmax=-inf;
        Ecnt=0;
        init();
        for (int i=1;i<=m;i++)
        {
            cin>>u>>v>>w;
            Add_Edge(u,v,w);
            Wmax=max(Wmax,w);
        }
        if (check(Wmax+1))
            cout<<"Infinite"<<endl;
        else
            if(!check(1))
                cout<<"No Solution"<<endl;
        else
        {
            int L,R;
            int Ans;
            L=1;
            R=Wmax;
            while (L<=R)
            {
                int mid=L+(R-L)/2;
                if (check(mid))
                {
                    Ans=mid;
                    L=mid+1;
                }
                else
                    R=mid-1;
            }
            cout<<Ans<<endl;
        }
    }
    return 0;
}

void init()
{
    memset(First,-1,sizeof(First));
    memset(Next,-1,sizeof(Next));
    memset(vis,0,sizeof(vis));
    Ecnt=0;
    return;
}

void Add_Edge(int u,int v,int w)
{
    Ecnt++;
    V[Ecnt]=v;
    W[Ecnt]=w;
    if (First[u]==-1)
    {
        First[u]=Ecnt;
        Last[u]=Ecnt;
    }
    else
    {
        Next[Last[u]]=Ecnt;
        Last[u]=Ecnt;
    }
    return;
}

bool check(int x)
{
    for (int i=1;i<=Ecnt;i++)
        W[i]=W[i]-x;
    bool flag=spfa();//有负环返回1,无负环返回0
    for (int i=1;i<=Ecnt;i++)
        W[i]=W[i]+x;
    return !flag;
}

bool spfa()
{
    queue<int> Q;
    memset(vis,0,sizeof(vis));
    memset(Tot,0,sizeof(Tot));
    for (int i=1;i<=n;i++)
    {
        Dist[i]=0;
        vis[i]=1;
        Q.push(i);
        //Tot[i]=1;
    }
    do
    {
        int u=Q.front();
        Q.pop();
        vis[u]=0;
        for (int i=First[u];i!=-1;i=Next[i])
        {
            int v=V[i];
            if (Dist[v]>Dist[u]+W[i])
            {
                Dist[v]=Dist[u]+W[i];
                if (vis[v]==0)
                {
                    Q.push(v);
                    Tot[v]++;
                    if (Tot[v]>n)
                        return true;
                }
            }
        }
    }
    while (!Q.empty());
    return false;
}
