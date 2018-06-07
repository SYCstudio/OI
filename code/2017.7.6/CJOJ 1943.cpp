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
vector<int> E[maxN];
int Match[maxN];
bool vis[maxN];

bool Hungary(int u);

int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    {
        int x;
        while (cin>>x)
        {
            if (x==0)
                break;
            E[i].push_back(x);
        }
    }
    int Ans=0;
    memset(Match,-1,sizeof(Match));
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if (Hungary(i))
            Ans++;
    }
    cout<<Ans<<endl;
    return 0;
}

bool Hungary(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1)||(Hungary(Match[v])))
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}