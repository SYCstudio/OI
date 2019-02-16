#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50001;
const int maxM=50001;
const int inf=2147483647;

int n,m;
int cnt;
int Map[maxN];
//Graph
int First[maxN];
int Last[maxN];
int Next[maxM];
int V[maxM];
//Tarjan
int dfn[maxN];
int low[maxN];
//Stack
stack<int> S;
bool instack[maxN];
//LTK
int LTKcnt;
int LTK[maxN];
int LTK_tot[maxN];
//GD
int GDcnt;
bool is_GD[maxN];
bool vis[maxN/100][maxN/100];//判重边，但不是去掉，而是用来避免重复累加
int GD_Degree[maxN];//统计每个连通块周围的割点数

void init();
int change(int x);
void Add_Edge(int u,int v);
void tarjan1(int u,int root);
void dfs(int u);

int main()
{
    int T=0;
    do
    {
        T++;
        int k,a,b;
        init();
        cin>>k;
        if (k==0)
            break;
        for (int i=1;i<=k;i++)
        {
            cin>>a>>b;
            Add_Edge(change(a),change(b));
            Add_Edge(change(b),change(a));
        }

        /*for (int i=1;i<=n;i++)
            cout<<i<<'['<<Map[i]<<']'<<' ';
        cout<<endl;/*

        for (int i=1;i<=n;i++)
        {
            cout<<i<<":"<<endl<<"   ";
            for (int j=First[i];j!=-1;j=Next[j])
                cout<<V[j]<<" ";
            cout<<endl;
        }*/

        m=cnt;
        cnt=0;
        for (int i=1;i<=n;i++)
            if (dfn[i]==0)
                tarjan1(i,i);

        //for (int i=1;i<=n;i++)
        //    if (is_GD[i]==1)
        //        cout<<i<<" ";
        //cout<<endl;

        if (GDcnt==0)
        {
            cout<<"Case "<<T<<": "<<2<<" "<<n*(n-1)/2<<endl;
            continue;
        }

        for (int i=1;i<=n;i++)
            if ((LTK[i]==-1)&&(is_GD[i]==0))
            {
                LTKcnt++;
                //cout<<LTKcnt<<":";
                dfs(i);
                //cout<<endl;
            }

        for (int i=1;i<=n;i++)
            if (is_GD[i]==1)
            {
                for (int j=First[i];j!=-1;j=Next[j])
                {
                    int v=V[j];
                    if ((is_GD[v]==0)&&(vis[i][LTK[v]]==0))
                    {
                        GD_Degree[LTK[v]]++;
                        vis[i][LTK[v]]=1;
                    }
                }
            }

        long long Method=1;
        long long Tot=0;

        for (int i=1;i<=LTKcnt;i++)
            if (GD_Degree[i]==1)
            {
                Tot++;
                Method*=(long long)(LTK_tot[i]);
                //cout<<'['<<i<<','<<LTK_tot[i]<<']'<<endl;
            }
        //cout<<endl;
        cout<<"Case "<<T<<": "<<Tot<<" "<<Method<<endl;
    }
    while (1);
}

void init()
{
    cnt=0;
    LTKcnt=0;
    GDcnt=0;
    n=0;
    mem(First,-1);
    mem(Next,-1);
    mem(Last,-1);
    mem(dfn,0);
    mem(instack,0);
    mem(is_GD,0);
    mem(Map,-1);
    mem(LTK,-1);
    mem(LTK_tot,0);
    mem(GD_Degree,0);
    mem(vis,0);
    while (!S.empty())
        S.pop();
    return;
}

int change(int x)
{
    if (Map[x]==-1)
    {
        n++;
        Map[x]=n;
    }
    return Map[x];
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


void tarjan1(int u,int root)
{
    if (is_GD[u]==1)
        return;
    int v;
    int childcnt=0;
    cnt++;
    dfn[u]=low[u]=cnt;

    for (int i=First[u];i!=-1;i=Next[i])
    {
        v=V[i];
        if (dfn[v]==0)
        {
            childcnt++;
            tarjan1(v,root);
            low[u]=min(low[u],low[v]);
            if ((u==root)&&(childcnt>=2)&&(is_GD[u]==0))
            {
                is_GD[u]=1;
                GDcnt++;
            }
            else
                if ((u!=root)&&(dfn[u]<=low[v])&&(is_GD[u]==0))
                {
                    is_GD[u]=1;
                    GDcnt++;
                }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    return;
}

void dfs(int u)
{
    LTK[u]=LTKcnt;
    LTK_tot[LTKcnt]++;
    //cout<<u<<" ";
    for (int i=First[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if ((LTK[v]==-1)&&(is_GD[v]==0))
            dfs(v);
    }
    return;
}
