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
bool vis[maxN];
 
void init();
void Add_Edge(int u,int v,int w);
void OK();
void dfs(int u);
 
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
        In[a]++;
    }
    for (int i=1;i<=md;i++)
    {
        cin>>a>>b>>d;
        Add_Edge(a,b,-d);
        In[b]++;
    }
    OK();
    queue<int> Q;
    for (int i=1;i<=n;i++)
        if (In[i]==0)
        {
            //cout<<"push"<<endl;
            Q.push(i);
            Dist[i]=0;
            vis[i]=1;
        }
        else
            Dist[i]=inf;
    do
    {
        int u=Q.front();
        vis[u]=0;
        Q.pop();
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
 
void OK()
{
    flag=0;
    for (int i=1;i<=n;i++)
        if (In[i]==0)
        {
            flag=1;
            dfs(i);
        }
    if (flag==0)
    {
        cout<<-1<<endl;
        exit(0);
    }
    memset(vis,0,sizeof(vis));
    return;
}
 
void dfs(int u)
{
    vis[u]=1;
    for (int i=First[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if (vis[v]==0)
        {
            dfs(v);
        }
        else
        {
            flag=0;
            cout<<-1<<endl;
            exit(0);
        }
    }
    vis[u]=0;
}