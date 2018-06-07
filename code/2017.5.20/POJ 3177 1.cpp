#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxsize=30000;
const int inf=2147483647;

int n,m;
int cnt;
//Graph
int First[maxsize];
int Last[maxsize];
int Next[maxsize];
int V[maxsize];
bool Map[maxsize][maxsize];//Хажи
//tarjan
int dfn[maxsize];
int low[maxsize];
//Degree
int Degree[maxsize];

void init();
void Add_Edge(int u,int v);
void tarjan(int u,int father);

int main()
{
    init();
    int a,b;
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>a>>b;
        if (Map[a][b]==0)
        {
            Add_Edge(a,b);
            Add_Edge(b,a);
            Map[a][b]=Map[b][a]=1;
        }
    }
    cnt=0;
    tarjan(1,1);
    for (int i=1;i<=n;i++)
        for (int j=First[i];j!=-1;j=Next[j])
            if (low[i]!=low[V[j]])
                Degree[low[i]]++;
    int tot=0;
    for (int i=1;i<=n;i++)
        if (Degree[i]==1)
            tot++;
    cout<<(tot+1)/2<<endl;
    return 0;
}

void init()
{
    cnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(Degree,0);
    mem(dfn,0);
    mem(Map,0);
    return;
}

void Add_Edge(int u,int v)
{
    cnt++;
    V[cnt]=v;
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

void tarjan(int u,int father)
{
    cnt++;
    dfn[u]=low[u]=cnt;
    for (int i=First[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if (dfn[v]==0)
        {
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else
            if (v!=father)
                low[u]=min(low[u],dfn[v]);
    }
    return;
}