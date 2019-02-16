#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cstring>
using namespace std;
 
const int maxN=1001;
const int maxM=10001;
const int inf=2147483647;
 
int n,m=0;
bool flag;
int V[maxM];
int W[maxM];
int First[maxN];
int Last[maxN];
int Next[maxM];
int In[maxN];
int Dist[maxN];
int Cnt[maxN];
bool vis[maxN];
 
void init();
void Add_Edge(int u,int v,int w);
 
int main()
{
    init();
    int ml,md;
    int a,b,d;
    cin>>n>>ml>>md;
    for (int i=1;i<=ml;i++)
    {
        cin>>a>>b>>d;
        Add_Edge(b,a,d);
        //In[b]++;
    }
    for (int i=1;i<=md;i++)
    {
        cin>>a>>b>>d;
        Add_Edge(a,b,-d);
        //In[a]++;
    }
    //OK();
    queue<int> Q;
    Q.push(n);
    Dist[n]=0;
    for (int i=1;i<=n-1;i++)
        Dist[i]=inf;
    do
    {
        int u=Q.front();
        vis[u]=0;
        Cnt[u]++;
        Q.pop();
        if (Cnt[u]>n)
        {
            cout<<-1<<endl;
            exit(0);
        }
        for (int i=First[u];i!=-1;i=Next[i])
        {
            int v=V[i];
            int w=W[i];
            if (Dist[v]>Dist[u]+w)
            {
                Dist[v]=Dist[u]+w;
                if (vis[v]==0)
                {
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    while (Q.empty()!=1);
    //for (int i=1;i<=n;i++)
    //    cout<<Dist[i]<<' ';
    //cout<<endl;
    if (Dist[1]==inf)
        cout<<-2<<endl;
    else
        cout<<Dist[1]<<endl;
    return 0;
}
 
void init()
{
    memset(First,-1,sizeof(First));
    memset(Next,-1,sizeof(Next));
    memset(In,0,sizeof(In));
    memset(vis,0,sizeof(vis));
    memset(Cnt,0,sizeof(Cnt));
}
 
void Add_Edge(int u,int v,int w)
{
    m++;
    V[m]=v;
    W[m]=w;
    if(First[u]==-1)
    {
        First[u]=m;
        Last[u]=m;
    }
    else
    {
        Next[Last[u]]=m;
        Last[u]=m;
    }
    return;
}