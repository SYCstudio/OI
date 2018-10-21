#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

class Edge
{
public:
    int v,w;
};

const int maxN=210000;
const int inf=2147483647;

int n,m;
vector<Edge> E[maxN];
int Depth[maxN];
int Dist[maxN];
int Parent[maxN][23];
bool vis[maxN];

void LCA_init();
void dfs(int u);
int LCA(int a,int b);

int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int a,b,c;
        char ch;
        scanf("%d%d%d",&a,&b,&c);
        cin>>ch;
        E[a].push_back((Edge){b,c});
        E[b].push_back((Edge){a,c});
    }
    LCA_init();
    int Q;
    scanf("%d",&Q);
    for (int i=1;i<=Q;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        cout<<Dist[u]+Dist[v]-2*Dist[LCA(u,v)]<<endl;
    }
    return 0;
}

void LCA_init()
{
    memset(Dist,0,sizeof(Dist));
    memset(Parent,0,sizeof(Parent));
    memset(Depth,0,sizeof(Depth));
    memset(vis,0,sizeof(vis));
    dfs(1);
    for (int j=1;j<=20;j++)
        for (int i=1;i<=n;i++)
            Parent[i][j]=Parent[Parent[i][j-1]][j-1];
    return;
}

void dfs(int u)
{
    vis[u]=1;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i].v;
        if (vis[v]==0)
        {
            Depth[v]=Depth[u]+1;
            Dist[v]=Dist[u]+E[u][i].w;
            Parent[v][0]=u;
            dfs(v);
        }
    }
    return;
}

int LCA(int a,int b)
{
    if (Depth[a]<Depth[b])
        swap(a,b);
    for (int i=20;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Depth[Parent[a][i]]>=Depth[b]))
            a=Parent[a][i];
    if (a==b)
        return a;
    for (int i=20;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Parent[b][i]!=0)&&(Parent[a][i]!=Parent[b][i]))
        {
            a=Parent[a][i];
            b=Parent[b][i];
        }
    return Parent[a][0];
}
