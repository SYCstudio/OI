#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
const int maxN=1001;
const int maxM=10001;
 
int N,M,K;
int cnt=0;
int First[maxN];
int Last[maxN];
int Next[maxM];
int E[maxM];
int W[maxM];
int Ans[maxM];
bool vis[maxN];
 
void Add(int u,int v,int w);
void dfs(int u,int dist);
 
int main()
{
 
    int u,v,w;
 
    mem(First,-1);
    mem(Next,-1);
    mem(Last,-1);
    mem(vis,0);
 
    cin>>N>>M>>K;
    for (int i=1;i<=M;i++)
    {
        cin>>u>>v>>w;
        Add(u,v,w);
    }
 
    cnt=0;
    vis[N]=1;
    dfs(N,0);
 
    sort(&Ans[1],&Ans[cnt+1]);
 
    for (int i=1;i<=cnt;i++)
        cout<<Ans[i]<<endl;
    if(cnt<K)
        for (int i=cnt+1;i<=K;i++)
            cout<<-1<<endl;
    fclose(stdin);
    fclose(stdout);
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
 
void dfs(int u,int dist)
{
    if (u==1)
    {
        cnt++;
        Ans[cnt]=dist;
        return;
    }
    for (int i=First[u];i!=-1;i=Next[i])
    {
        if (vis[E[i]]==0)
        {
            vis[E[i]]=1;
            dfs(E[i],dist+W[i]);
            vis[E[i]]=0;
        }
    }
    return;
}
