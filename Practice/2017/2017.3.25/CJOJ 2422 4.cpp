#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
class Node
{
public:
    int u,w,sumw;
    Node(int a,int b,int c)
    {
        u=a;
        w=b;
        sumw=c;
    }
};
 
bool operator < (Node a,Node b)
{
    return a.w>b.w;
}
 
const int maxN=2001;
const int maxM=20001;
const int inf=2147483647;
 
int N,M,K;
int cnt=0;
int First[maxN];
int Last[maxM];
int Next[maxM];
int E[maxM];
int W[maxM];
int Dist[maxN];
bool vis[maxM];
bool Del[maxM];
 
void Add(int u,int v,int w);
void spfa();
void bfs();
 
int main()
{
    int u,v,w;
 
    mem(First,-1);
    mem(Next,-1);
    mem(Last,-1);
    mem(vis,0);
    mem(Del,0);
 
    cin>>N>>M>>K;
    for (int i=1;i<=M;i++)
    {
        cin>>u>>v>>w;
        Add(u,v,w);
        Add(v,u,w);
    }
    spfa();
    //cout<<"SPFA"<<endl;
    for (int i=1;i<=M;i++)
        Del[i*2]=1;
    bfs();
    return 0;
}
 
void Add(int u,int v,int w)
{
    cnt++;
    E[cnt]=v;
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
 
void spfa()
{
    mem(vis,0);
    for (int i=1;i<=N;i++)
        Dist[i]=inf/2-1;
    Dist[1]=0;
    queue<int> Q;
    Q.push(1);
    do
    {
        int u=Q.front();
        //cout<<u<<endl;
        Q.pop();
        vis[u]=0;
        for (int i=First[u];i!=-1;i=Next[i])
        {
            int v=E[i];
            if (Dist[u]+W[i]<Dist[v])
            {
                Dist[v]=Dist[u]+W[i];
                if (vis[v]==0)
                {
                    vis[u]=1;
                    Q.push(v);
                }
            }
        }
    }
    while (!Q.empty());
    //for (int i=1;i<=N;i++)
    //    cout<<Dist[i]<<" ";
    //cout<<endl;
    return;
}
 
void bfs()
{
    priority_queue<Node> Q;
    Q.push(Node(N,0,Dist[N]));
    do
    {
        Node P=Q.top();
        Q.pop();
        int u=P.u,lw=P.w,sumw=P.sumw;
        if (u==1)
        {
            cout<<sumw<<endl;
            K--;
        }
        if (K==0)
            break;
        for (int i=First[u];i!=-1;i=Next[i])
        {
            if (Del[i]==0)
            {
                int v=E[i],w=W[i];
                Q.push(Node(v,lw+w,lw+w+Dist[v]));
            }
        }
    }
    while (!Q.empty());
    for (int i=1;i<=K;i++)
        cout<<-1<<endl;
}
