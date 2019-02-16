#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=10001;
const int inf=2147483647;

int n;
int cnt;
int dfn[maxN];
int Ord[maxN];
int F[maxN];
vector<int> E[maxN];
bool FG[maxN];//标记某个点是否已经覆盖
bool In_set[maxN];//标记某个点是否被选进集合

void dfs(int u);

int main()
{
    memset(dfn,-1,sizeof(dfn));
    memset(F,0,sizeof(F));
    cin>>n;
    for (int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    cnt=0;
    dfs(1);
    int Ans=0;
    memset(In_set,0,sizeof(In_set));
    memset(FG,0,sizeof(FG));
    for (int i=n;i>=1;i--)
    {
        int u=Ord[i];
        if (FG[u]==0)
        {
            if (In_set[F[u]]==0)
            {
                In_set[F[u]]=1;
                Ans++;
            }
            FG[u]=1;
            FG[F[u]]=1;
            FG[F[F[u]]]=1;
        }
    }
    cout<<Ans<<endl;
    return 0;
}

void dfs(int u)
{
    cnt++;
    dfn[u]=cnt;
    Ord[cnt]=u;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (dfn[v]==-1)
        {
            F[v]=u;
            dfs(v);
        }
    }
}