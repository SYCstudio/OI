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
 
const int maxN=200;
const int inf=2147483647;
 
int n,Q;
vector<Edge> E[maxN];
bool vis[maxN];
int F[maxN][maxN]={0};
 
int dfs(int u);
 
int main()
{
    int u,v,w;
    cin>>n>>Q;
    for (int i=1;i<n;i++)
    {
        cin>>u>>v>>w;
        E[u].push_back((Edge){v,w});
        E[v].push_back((Edge){u,w});
    }
    memset(vis,0,sizeof(vis));
    dfs(1);
    cout<<F[1][Q]<<endl;
    return 0;
}
 
int dfs(int u)
{
    int cnt=0;//统计子树枝个数
    vis[u]=1;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i].v;
        if (vis[v]==0)
        {
            cnt+=dfs(v)+1;//每次要+1，即加上u->v这条边
            for (int j=min(Q,cnt);j>=1;j--)//要取min的原因是要简化循环
                for (int k=j;k>=1;k--)
                {
                    F[u][j]=max(F[u][j],F[u][j-k]+F[v][k-1]+E[u][i].w);
                }
        }
    }
    return cnt;
}