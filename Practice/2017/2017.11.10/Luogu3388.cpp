#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=maxN*2;
const int inf=2147483647;

int n,m;
int cnt=0,Head[maxN],Next[maxM],V[maxM];
int dfscnt=0,dfn[maxN],low[maxN];
vector<int> Ans;

void Add_Edge(int u,int v);
void Tarjan(int u,int father);

int main()
{
    mem(Head,-1);mem(dfn,0);Ans.clear();
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
	int u,v;
	scanf("%d%d",&u,&v);
	Add_Edge(u,v);Add_Edge(v,u);
    }
    for (int i=1;i<=n;i++)
	if (dfn[i]==0)
	    Tarjan(i,i);
    sort(Ans.begin(),Ans.end());
    for (int i=0;i<Ans.size();i++) printf("%d\n",Ans[i]);
    return 0;
}

void Add_Edge(int u,int v)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;
    return;
}

void Tarjan(int u,int father)
{
    dfscnt++;
    dfn[u]=low[u]=dfscnt;
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	int v=V[i];if (v==father) continue;
	if (dfn[v]==0)
	{
	    Tarjan(v,u);
	    low[u]=min(low[u],low[v]);
	}
	else low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]) Ans.push_back(u);
    return;
}
