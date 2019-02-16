#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x-1)*n+y)

const int maxMap=201;
const int maxN=maxMap*maxMap;
const int maxM=maxN*8*2;
const int F1[9]={0,-1,-2,-2,-1,1,2,2,1};
const int F2[9]={0,-2,-1,1,2,2,1,-1,-2};
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m,S,T;
bool Map[maxMap][maxMap];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Queue[maxM],Depth[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
void _Add(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		Map[x][y]=1;
	}
	S=n*n+1;T=n*n+2;
	int Sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (Map[i][j]) continue;
			if (i%2==j%2)
			{
				Sum++;
				Add_Edge(S,Id(i,j),1);
				for (int k=1;k<=8;k++)
				{
					int x=i+F1[k],y=j+F2[k];
					if ((x<=0)||(y<=0)||(x>n)||(y>n)||(Map[x][y])) continue;
					Add_Edge(Id(i,j),Id(x,y),inf);
				}
			}
			else Add_Edge(Id(i,j),T,1);
		}
	int Flow=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) Flow+=di;
	}
	printf("%d\n",n*n-m-Flow);
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	_Add(u,v,flow);_Add(v,u,0);
	return;
}

void _Add(int u,int v,int flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].flow=flow;
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
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1)) Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (t!=h);
	if (Depth[T]==-1) return 0;
	return 1;
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
