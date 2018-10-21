#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
using namespace std;
 
const int maxsize=10001;
const int inf=2147483647;
 
int n,m;
int cnt;
int First[maxsize];
int Next[maxsize];
int V[maxsize];
int W[maxsize];
int Last[maxsize];
int Dist[maxsize];
bool vis[maxsize];
int Cnt[maxsize];
 
inline void Add_Edge(int u,int v,int w);
 
int main()
{
    int a,b;
    cin>>n>>m;
    cnt=0;
    memset(First,-1,sizeof(First));
    memset(Next,-1,sizeof(Next));
    memset(Last,-1,sizeof(Last));
    memset(vis,0,sizeof(vis));
    memset(Cnt,0,sizeof(Cnt));
    for (int i=1;i<=m;i++)
    {
        cin>>a>>b;
        Add_Edge(a,b,-1);
    }
    queue<int> Q;
    for (int i=1;i<=n;i++)
        Dist[i]=inf;
    Dist[1]=0;
    Q.push(1);
    do
    {
        int u=Q.front();
        vis[u]=0;
        Cnt[u]++;
        Q.pop();
        if (Cnt[u]>n)
        {
            cout<<"impossible"<<endl;
            return 0;
        }
        for (int i=First[u];i!=-1;i=Next[i])
        {
            int v=V[i];
            if (Dist[v]>Dist[u]+W[i])
            {
                Dist[v]=Dist[u]+W[i];
                if (vis[v]==0)
                {
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    while (!Q.empty());
    int Min=inf;
    for (int i=1;i<=n;i++)
    {
        Min=min(Min,Dist[i]);
        if (Dist[i]==inf)
        {
            cout<<"impossible"<<endl;
            return 0;
        }
    }
    int Sum=0;
    for (int i=1;i<=n;i++)
        Sum=Sum+Dist[i]-Min;
    cout<<Sum+n*100<<endl;
    //for (int i=1;i<=n;i++)
    //    cout<<Dist[i]<<" ";
    //cout<<endl;
}
 
inline void Add_Edge(int u,int v,int w)
{
    cnt++;
    V[cnt]=v;
    W[cnt]=w;
    if (First[u]==-1)
    {
        First[u]=cnt;
        Last[u]=cnt;
    }
    else
    {
        Next[Last[u]]=cnt;
        Last[u]=cnt;
    }
    return;
}