#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

class Edge1
{
public:
    int v,w;
};

class Edge2
{
public:
    int u,v,w;
};

bool operator < (Edge2 a,Edge2 b)
{
    return a.w<b.w;
}

const int maxN=100010;
const int maxM=300010;
const int inf=2147483647;

int n,m;
Edge2 E[maxM];
vector<Edge1> T[maxN];
//Union_Find_Set
int Mayuri[maxN];
//LCA
int Parent[maxN][25];
int Path[maxN][25];
int Depth[maxN];
bool vis[maxN];

int read();
void MST();
int Find(int u);
bool Union(int u,int v);
void LCA_init();
void dfs(int u);
int LCA(int a,int b);

int main()
{
    n=read();m=read();
    for (int i=1;i<=m;i++)
    {
        E[i].u=read();
        E[i].v=read();
        E[i].w=read();
    }
    MST();//求最小生成树
    LCA_init();//LCA的各种信息初始化
    int Q=read();
    for (int i=1;i<=Q;i++)
    {
        int x=LCA(read(),read());
        if (x==-1)
            cout<<"impossible"<<endl;//注意无解的情况，即这两点不连通，可以用并查集判断
        else
            cout<<x<<endl;
    }
    return 0;
}

int read()//读入优化
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch<'0')||(ch>'9'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch>='0')&&(ch<='9'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

void MST()//求最小生成树，这里用克鲁斯卡尔算法
{
    sort(&E[1],&E[m+1]);
    for (int i=1;i<=n;i++)//并查集初始化
        Mayuri[i]=i;
    int cnt=0;
    for (int i=1;i<=m;i++)
    {
        int u=E[i].u;
        int v=E[i].v;
        int w=E[i].w;
        if (Union(u,v))
        {
            T[u].push_back((Edge1){v,w});
            T[v].push_back((Edge1){u,w});
            cnt++;
            if (cnt==n-1)
                break;
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

void LCA_init()
{
    memset(Parent,0,sizeof(Parent));
    memset(Path,0,sizeof(Path));
    memset(Depth,0,sizeof(Depth));
    memset(vis,0,sizeof(vis));
    dfs(1);
    for (int j=1;j<=20;j++)
        for (int i=1;i<=n;i++)
        {
            Parent[i][j]=Parent[Parent[i][j-1]][j-1];
            Path[i][j]=max(Path[i][j-1],Path[Parent[i][j-1]][j-1]);//同时求解Path
        }
    return;
}

void dfs(int u)
{
    vis[u]=1;
    for (int i=0;i<T[u].size();i++)
    {
        int v=T[u][i].v;
        if (vis[v]==0)
        {
            Depth[v]=Depth[u]+1;
            Parent[v][0]=u;
            Path[v][0]=T[u][i].w;//记录Path的初值
            dfs(v);
        }
    }
}

int LCA(int a,int b)
{
    if (Find(a)!=Find(b))
    {
        return -1;
    }
    int max_path=0;
    if (Depth[a]<Depth[b])
        swap(a,b);
    for (int i=20;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Depth[Parent[a][i]]>=Depth[b]))
        {
            max_path=max(max_path,Path[a][i]);//同时更新当前的最大边权
            a=Parent[a][i];
        }
    if (a==b)
        return max_path;
    for (int i=20;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Parent[b][i]!=0)&&(Parent[a][i]!=Parent[b][i]))
        {
            max_path=max(max_path,Path[a][i]);//这里也是更新当前的最大边权
            max_path=max(max_path,Path[b][i]);
            a=Parent[a][i];
            b=Parent[b][i];
        }
    max_path=max(max_path,Path[a][0]);//最后要注意再与Path[a][0]和Path[b][0]比较一下，因为在原来的LCA中，公共祖先是Parent[a][0]或Parent[b][0]
    max_path=max(max_path,Path[b][0]);
    return max_path;
}