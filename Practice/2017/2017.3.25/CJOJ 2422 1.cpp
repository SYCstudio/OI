#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
const int maxN=505;
const int maxM=5005;
const int inf=2147483647;
 
int n,m;
int S,T;
int cnt=0;
int ansmax,ansmin;
int First[maxN];
int Next[maxM];
int Last[maxN];
int V[maxM];
int E[maxM];
bool vis[maxN];
 
void Add(int u,int v,int w);
void dfs(int u,int maxv,int minv);
int gcd(int x,int y);
 
int main()
{
 
    int u,v,w;
    mem(First,-1);
    mem(Next,-1);
    mem(Last,-1);
    mem(vis,0);
    ansmin=1;
    ansmax=inf;
 
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        Add(u,v,w);
        Add(v,u,w);
    }
    cin>>S>>T;
 
    vis[S]=1;
    dfs(S,0,inf);
 
    //cout<<ansmax<<" "<<ansmin<<endl;
    if (ansmax==inf)
    {
        cout<<"IMPOSSIBLE"<<endl;
        fclose(stdin);
        fclose(stdout);
        return 0;
    }
 
    int p=gcd(ansmax,ansmin);
 
    while (p!=1)
    {
        ansmax=ansmax/p;
        ansmin=ansmin/p;
        p=gcd(ansmax,ansmin);
    }
 
    if (ansmin==1)
    {
        cout<<ansmax<<endl;
    }
    else
    {
        cout<<ansmax<<'/'<<ansmin<<endl;
    }
 
    fclose(stdin);
    fclose(stdout);
}
 
void Add(int u,int v,int w)
{
    cnt++;
    E[cnt]=v;
    V[cnt]=w;
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
 
void dfs(int u,int maxv,int minv)
{
    if (u==T)
    {
        if ( ((double)maxv/(double)minv) < ((double)ansmax/(double)ansmin) )
        {
            ansmax=maxv;
            ansmin=minv;
        }
        return;
    }
    for (int i=First[u];i!=-1;i=Next[i])
    {
        if (vis[E[i]]==0)
        {
            vis[E[i]]=1;
            dfs(E[i],max(maxv,V[i]),min(minv,V[i]));
            vis[E[i]]=0;
        }
    }
    return;
}
 
int gcd(int x,int y)
{
    int z=x%y;
    while (z!=0)
    {
        x=y;
        y=z;
        z=x%y;
    }
    return y;
}
