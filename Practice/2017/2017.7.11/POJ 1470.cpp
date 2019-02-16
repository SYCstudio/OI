#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=901;
const int inf=2147483647;

int n;
int root;
vector<int> E[maxN];
int Parent[maxN][20];
int Depth[maxN];
int Cnt[maxN];
bool vis[maxN];

void LCA_init();
void dfs(int u);
int LCA(int a,int b);

int main()
{
    while (cin>>n)
    {
        for (int i=1;i<=n;i++)
            E[i].clear();
        memset(Parent,0,sizeof(Parent));
        memset(Depth,0,sizeof(Depth));
        memset(Cnt,0,sizeof(Cnt));
        memset(vis,0,sizeof(vis));
        for (int i=1;i<=n;i++)//-------输入开始-------
        {
            int u,nn;
            scanf("%d:(%d)",&u,&nn);
            for (int j=1;j<=nn;j++)
            {
                int v;
                scanf("%d",&v);
                E[u].push_back(v);
                vis[v]=1;
            }
        }
        for (int i=1;i<=n;i++)
            if (vis[i]==0)
            {
                root=i;
                break;
            }
        LCA_init();
        int Q;
        scanf("%d",&Q);
        for (int i=1;i<=Q;i++)
        {
            int u,v;
            scanf(" (%d %d)",&u,&v);
            //cout<<LCA(u,v)<<endl;
            Cnt[LCA(u,v)]++;
        }//-------输入结束-------
        for (int i=1;i<=n;i++)
            if (Cnt[i]!=0)
                printf("%d:%d\n",i,Cnt[i]);
    }
    return 0;
}

void LCA_init()//LCA初始化
{
    Depth[root]=0;
    dfs(root);
    /*for (int i=1;i<=n;i++)
    {
        for (int j=0;j<=15;j++)
            cout<<Parent[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;*/
    for (int j=1;j<=15;j++)
        for (int i=1;i<=n;i++)
            Parent[i][j]=Parent[Parent[i][j-1]][j-1];
    /*for (int i=1;i<=n;i++)
    {
        for (int j=0;j<=15;j++)
            cout<<Parent[i][j]<<' ';
        cout<<endl;
    }*/
    return;
}

void dfs(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        Depth[v]=Depth[u]+1;
        Parent[v][0]=u;
        //cout<<"---"<<v<<' '<<Parent[v][0]<<endl;
        dfs(v);
    }
    return;
}

int LCA(int a,int b)//倍增法计算LCA
{
    if (Depth[a]<Depth[b])
        swap(a,b);
    for (int i=15;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Depth[Parent[a][i]]>=Depth[b]))
            a=Parent[a][i];
    if (a==b)
        return a;
    for (int i=15;i>=0;i--)
        if ((Parent[a][i]!=0)&&(Parent[b][i]!=0)&&(Parent[a][i]!=Parent[b][i]))
        {
            a=Parent[a][i];
            b=Parent[b][i];
        }
    return Parent[a][0];
}