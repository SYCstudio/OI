#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=10011;
const int inf=2147483647;

int n;
int root;
vector<int> E[maxN];
int Parent[maxN][25];
int Depth[maxN];
bool vis[maxN];

int read();
void LCA_init();
void dfs(int u);
int LCA(int a,int b);

int main()
{
    int TT;
    TT=read();
    for (int ti=1;ti<=TT;ti++)
    {
        n=read();
        for (int i=1;i<=n;i++)
            E[i].clear();
        memset(vis,0,sizeof(vis));
        for (int i=1;i<n;i++)
        {
            int x=read(),y=read();
            E[x].push_back(y);
            vis[y]=1;
        }
        for (int i=1;i<=n;i++)
            if (vis[i]==0)
                root=i;
        //cout<<root<<endl;
        LCA_init();
        cout<<LCA(read(),read())<<endl;
    }
    return 0;
}

int read()
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch>'9')||(ch<'0'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

void LCA_init()
{
    memset(Depth,0,sizeof(Depth));
    Depth[root]=0;
    memset(Parent,0,sizeof(Parent));
    dfs(root);
    int kk=0;
    for (int j=1;j<=20;j++)
        for (int i=1;i<=n;i++)
            Parent[i][j]=Parent[Parent[i][j-1]][j-1];
    /*for (int i=1;i<=n;i++)
    {
        for (int j=0;j<=kk;j++)
            cout<<Parent[i][j]<<' ';
        cout<<endl;
    }
    */
}

void dfs(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        Depth[v]=Depth[u]+1;
        Parent[v][0]=u;
        dfs(v);
    }
    return;
}

int LCA(int a,int b)
{
    if (Depth[b]>Depth[a])
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
