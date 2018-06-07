#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=300;
const int inf=2147483647;

int n,m;
vector<int> E[maxN];//存边
bool vis[maxN];//牛棚是否已经访问过，避免重复
int Match[maxN];//存下牛棚匹配的牛的编号，-1表示还未匹配

bool dfs(int u);

int main()
{
    while(cin>>n>>m)
    {
for (int i=1;i<=n;i++)
E[i].clear();
    for (int i=1;i<=n;i++)
    {
        int S;
        cin>>S;
        for (int j=1;j<=S;j++)
        {
            int x;
            cin>>x;
            E[i].push_back(x);//连边
        }
    }

    memset(Match,-1,sizeof(Match));
    int cnt=0;
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));//每一次进行匹配之前都要清空
        if (dfs(i))//若成功匹配，则最大匹配数+1，因为多有一个点能够匹配
            cnt++;
    }
    cout<<cnt<<endl;
    }
    return 0;
}

bool dfs(int u)//1表示匹配成功，0表示不成功
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1) || dfs(Match[v]))//若当前牛棚可以匹配，或是dfs返回1（说明在dfs中成功匹配了），则此时要将新的值更新进去，同时向上一级dfs传值1
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}