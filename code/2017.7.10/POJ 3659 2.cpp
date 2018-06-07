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
vector<int> E[maxN];
int F[maxN][5]={0};
bool vis[maxN];

void dfs(int u);

int main()
{
    cin>>n;
    for (int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    memset(vis,0,sizeof(vis));
    dfs(1);
    cout<<min(F[1][0],F[1][1])<<endl;
    return 0;
}

void dfs(int u)
{
    F[u][0]=1;
    F[u][2]=0;
    F[u][1]=0;
    vis[u]=1;
    bool flag=0;//标记u的子树中计算F[u][1]时是否取过F[v][0]
    int inc=inf;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            dfs(v);
            F[u][0]+=min(F[v][0],min(F[v][1],F[v][2]));
            F[u][2]+=min(F[v][1],F[v][0]);
            if (F[v][0]<=F[v][1])//这里就是对F[u][1]的处理啦，另外注意这里要取等
            {
                flag=1;
                F[u][1]+=F[v][0];
            }
            else
            {
                inc=min(inc,(F[v][0]-F[v][1]));
                F[u][1]+=F[v][1];
            }
        }
    }
    if (flag==0)//若在计算F[u][1]时没有从F[v][0]推导过来的，就要强制将一个转换成从F[v][0]推导过来。
    {
        F[u][1]+=inc;
    }
    return;
}