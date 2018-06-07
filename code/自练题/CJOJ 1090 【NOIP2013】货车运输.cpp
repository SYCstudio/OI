#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

class EDGE
{
public:
    int u,v,w;
    bool ok;
};
class EDGE2
{
public:
    int v,w;
    //EDGE2{v(v),w(w)}
};

const int maxN=10001;
const int maxM=50001;
const int inf=2147483647;

int n,m;
int cnt=0;
//Graph1
EDGE Edge[maxM*2];
//Graph2
vector<EDGE2> E[maxN];
//Mayuri
int Mayuri[maxN];
//LCA
int Depth[maxN];
int Parent[maxN][30];
int Path[maxN][30];
//dfs
bool vis[maxN];

void max_tree();//求最大树
bool cmp(EDGE a,EDGE b);
int Find(int u);
bool Union(int u,int v);
void build_tree();
void dfs(int u,int father,int deep);//dfs求深度
void LCA_init();
int LCA(int u,int v);

int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>Edge[i].u>>Edge[i].v>>Edge[i].w;
        Edge[i].ok=0;
    }
    max_tree();
    //cout<<"max_tree"<<endl;
    //for (int i=1;i<=m;i++)
    //    if (Edge[i].ok==1)
    //        cout<<Edge[i].u<<' '<<Edge[i].v<<' '<<Edge[i].w<<endl;
    build_tree();
    LCA_init();
    int P;
    int u,v;
    cin>>P;
    for (int i=1;i<=P;i++)
    {
        cin>>u>>v;
        cout<<LCA(u,v)<<endl;
    }
}

bool cmp(EDGE a,EDGE b)
{
    return a.w>b.w;
}

void max_tree()
{
    sort(&Edge[1],&Edge[m+1],cmp);
    //cout<<"sort"<<endl;
    //for (int i=1;i<=m;i++)
    //    cout<<Edge[i].u<<' '<<Edge[i].v<<' '<<Edge[i].w<<endl;

    for (int i=1;i<=n;i++)
            Mayuri[i]=i;

    int tot=0;
    int i=0;
    while ((tot<n-1)&&(i<m))
    {
        i++;
        if (Union(Edge[i].u,Edge[i].v))
        {
            tot++;
            Edge[i].ok=1;
        }
    }
    return;
}

int Find(int u)
{
    if (Mayuri[u]!=u)
        Mayuri[u]=Find(Mayuri[u]);
    return Mayuri[u];
}

bool Union(int u,int v)
{
    int fu=Find(u);
    int fv=Find(v);
    if (fu!=fv)
    {
        Mayuri[fu]=fv;
        return 1;
    }
    return 0;
}

void build_tree()
{
    EDGE2 e2;
    for (int i=1;i<=m;i++)
    {
        if (Edge[i].ok==1)
        {
            int u=Edge[i].u;
            int v=Edge[i].v;
            int w=Edge[i].w;
            E[u].push_back((EDGE2){v,w});
            E[v].push_back((EDGE2){u,w});
        }
    }
    /*cout<<"Build_Tree Result:"<<endl;
    for (int i=1;i<=n;i++)
    {
        cout<<i<<':'<<endl;
        for (int j=0;j<E[i].size();j++)
            cout<<E[i][j].v<<' '<<E[i][j].w<<endl;
        cout<<endl;
    }*/
    memset(vis,0,sizeof(vis));
    memset(Path,0,sizeof(Path));
    for (int i=1;i<=n;i++)
        if (vis[i]==0)
        {
            dfs(i,i,0);
        }
    /*for (int i=1;i<=n;i++)
        cout<<Depth[i]<<' ';
    cout<<endl;*/
    return;
}

void dfs(int u,int father,int deep)
{
    vis[u]=1;
    Depth[u]=deep;
    Parent[u][0]=father;
    for (int i=0;i<E[u].size();i++)
        if (vis[E[u][i].v]==0)
        {
            Path[E[u][i].v][0]=E[u][i].w;
            dfs(E[u][i].v,u,deep+1);
        }
    return;
}

void LCA_init()
{
    /*cout<<"LCA init begin:"<<endl;
    for (int i=1;i<=n;i++)
    {
        //cout<<Parent[i][0]<<' ';
        for (int j=0;(1<<(j-1))<=n;j++)
            cout<<Parent[i][j]<<' ';
        cout<<endl;
    }*/
    for (int j=1;(1<<(j-1))<=n;j++)
        for (int i=1;i<=n;i++)
            if (Depth[i]-(1<<(j-1))>=1)
            {
                Parent[i][j]=Parent[Parent[i][j-1]][j-1];
                Path[i][j]=min(Path[i][j-1],Path[Parent[i][j-1]][j-1]);
            }
    /*cout<<"LCA init result:"<<endl;
    for (int i=1;i<=n;i++)
    {
        //cout<<Parent[i][0]<<' ';
        for (int j=0;(1<<(j-1))<=n;j++)
            cout<<Parent[i][j]<<' ';
        cout<<endl;
    }
    for (int i=1;i<=n;i++)
    {
        //cout<<Parent[i][0]<<' ';
        for (int j=0;(1<<(j-1))<=n;j++)
            cout<<Path[i][j]<<' ';
        cout<<endl;
    }*/
    return;
}

int LCA(int u,int v)
{
    if (Find(u)!=Find(v))
        return -1;
    if (u==v)
        return 0;
    int min_path=inf;
    if (Depth[u]<Depth[v])
        swap(u,v);
    int maxj=1;
    while ((1<<maxj)<=Depth[u])
        maxj++;
    if (Depth[u]!=Depth[v])
    {
        for (int i=maxj;i>=0;i--)
            if ((Parent[u][i])&&(Path[u][i]))
            if (Depth[Parent[u][i]]>=Depth[v])
            {
                //cout<<min_path<<' '<<Path[u][i]<<endl;
                min_path=min(min_path,Path[u][i]);
                u=Parent[u][i];
            }
    }
    //cout<<u<<' '<<v<<endl;
    if (u==v)
        return min_path;
    maxj=0;
    while ((1<<maxj)<=Depth[v])
        maxj++;
    for (int i=maxj;i>=0;i--)
        if (Parent[u][i]!=Parent[v][i])
        {
            min_path=min(min_path,Path[u][i]);
            min_path=min(min_path,Path[v][i]);
            u=Parent[u][i];
            v=Parent[v][i];
        }
    return min(min_path,min(Path[u][0],Path[v][0]));
}
