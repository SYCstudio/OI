#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
const int maxN=100001*2;
const int maxM=200001*2;
const int inf=2147483647;
 
int n,m;
int cnt;
int First[maxN];
int Last[maxN];
int Next[maxM];
int V[maxM];
int dfn[maxN];
int low[maxN];
long long Num[maxN];
bool is_GD[maxN];
 
void init();
void Add_Edge(int u,int v);
long long tarjan(int u,int root,int father);
 
int main()
{
    //freopen("map_2016.in","r",stdin);
    //freopen("map_2016.out","w",stdout);
 
    int a,b;
 
    init();
 
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        Add_Edge(a,b);
        Add_Edge(b,a);
    }
 
    cnt=0;
    tarjan(1,1,1);
 
    /*for (int i=1;i<=n;i++)
        cout<<dfn[i]<<' ';
    cout<<endl;
    for (int i=1;i<=n;i++)
        cout<<low[i]<<' ';
    cout<<endl;
    for (int i=1;i<=n;i++)
        cout<<is_GD[i]<<' ';
    cout<<endl;
    for (int i=1;i<=n;i++)
        cout<<Num[i]<<' ';
    cout<<endl;*/
 
    for (int i=1;i<=n;i++)
        if (is_GD[i]==1)
            cout<<(Num[i]+(long long)(n-1))*2<<endl;
        else
            cout<<(n-1)*2<<endl;
 
    fclose(stdin);
    fclose(stdout);
    return 0;
}
 
void init()
{
    cnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(dfn,0);
    mem(Num,0);
    mem(is_GD,0);
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
 
long long tarjan(int u,int root,int father)
{
    int child=0;
    vector<long long> Sum;
    long long tot=0;
    long long tot2=0;
    cnt++;
    dfn[u]=low[u]=cnt;
 
    for (int i=First[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if (v==father)
            continue;
        if (dfn[v]==0)
        {
            /*cout<<u<<'-'<<v<<endl;
            for (int i=1;i<=n;i++)
                cout<<dfn[i]<<' ';
            cout<<endl;
            for (int i=1;i<=n;i++)
                cout<<low[i]<<' ';
            cout<<endl;*/
            long long K=tarjan(v,root,u);
            tot+=K;
 
            low[u]=min(low[u],low[v]);
            //child++;
            //Sum[child]=K;
            if (low[v]>=dfn[u])
            {
                tot2+=K;
                child++;
                Sum.push_back(K);
                is_GD[u]=1;
            }
        }
        else
            if (v!=father)
                low[u]=min(low[u],dfn[v]);
    }
    if ((u==root)&&(child==1))
        is_GD[u]=0;
    //cout<<"Node "<<u<<endl;
    if (u!=root)
    {
        child++;
        Sum.push_back(n-tot2-1);
    }
    //for (int i=1;i<=child;i++)
    //    cout<<Sum[i]<<' ';
    //cout<<endl;
    for (int i=1;i<child;i++)
        for (int j=i+1;j<=child;j++)
            Num[u]=Num[u]+Sum[i-1]*Sum[j-1];
    return tot+1;
}
