#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51*4;
const int maxM=maxN*100;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,K,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
char Input[maxN];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n>>K;S=n*4+1;T=S+1;
	for (int i=1;i<=n;i++) Add_Edge(S,i,0),Add_Edge(i,i+n+n,K);
	for (int i=1;i<=n;i++) Add_Edge(i+n,T,0),Add_Edge(i+n+n+n,i+n,K);
	for (int i=1;i<=n;i++)
	{
		cin>>(Input+1);
		for (int j=1;j<=n;j++)
			if (Input[j]=='Y') Add_Edge(i,j+n,1);
			else Add_Edge(i+n+n,j+n+n+n,1);
	}
	int round=0,mxflow=0;
	do
	{
		while (Bfs())
		{
			for (int i=1;i<=T;i++) cur[i]=Head[i];
			while (int di=dfs(S,inf)) mxflow+=di;
		}
		if (mxflow!=round*n) break;
		round++;
		for (int i=Head[S];i!=-1;i=Next[i])
			if ((E[i].v>=1)&&(E[i].v<=n)) E[i].flow++;
		for (int i=Head[T];i!=-1;i=Next[i])
			if ((E[i].v>=n+1)&&(E[i].v<=n+n)) E[i^1].flow++;
	}
	while (1);
	printf("%d\n",round-1);
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;
	E[edgecnt].v=u;E[edgecnt].flow=0;
	return;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;Queue[1]=S;Depth[S]=1;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((Depth[E[i].v]==-1)&&(E[i].flow>0))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (h!=t);
	if (Depth[T]!=-1) return 1;
	return 0;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
		{
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
