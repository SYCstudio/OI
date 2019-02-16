#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=10001;
const int inf=147483647;

int n;
int cnt;
vector<int> E[maxN];
bool vis[maxN];
int F[maxN][5];

void dfs(int u);

int main()
{
    while (cin>>n)
    {
        if (n==-1)
            break;
        for (int i=1;i<=n;i++)
            E[i].clear();
        for (int i=1;i<n;i++)
        {
            int x,y;
            cin>>x>>y;
            E[x].push_back(y);
            E[y].push_back(x);
        }
        int A;
        cin>>A;
        memset(vis,0,sizeof(vis));
        memset(F,0,sizeof(vis));
        dfs(1);
        cout<<min(F[1][1],F[1][0])<<endl;
        if (A==-1)
            break;
    }
    return 0;
}

void dfs(int u)
{
    vis[u]=1;
    F[u][0]=1;
    F[u][2]=0;
    F[u][1]=inf;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            dfs(v);
            F[u][0]+=min(F[v][0],F[v][2]);
            F[u][2]+=F[v][1];
            F[u][1]=min(F[u][1],F[v][0]-F[v][1]);//巧妙之处在这里，这样就可以保证除了选出的F[v][0]-F[v][1]最小的v是从F[v][0]得到
        }
    }
    F[u][1]+=F[u][2];//还有这里，最后加上所有的F[v][1]之和
    return;
}