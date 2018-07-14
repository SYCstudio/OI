#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*10;
const int maxM=202000*10;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	tarjan(1,0);
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[+=edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}


void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
			}
			else low[u]=min(low[u],dfn[v]);
		}
}
