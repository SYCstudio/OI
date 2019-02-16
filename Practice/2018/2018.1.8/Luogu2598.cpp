#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x-1)*m+y)

const int maxMap=101;
const int maxN=maxMap*maxMap;
const int maxM=maxN*200;
const int F1[5]={0,0,0,1,-1};
const int F2[5]={0,1,-1,0,0};
const int inf=2147483647;

class Edge
{
public:
    int v,flow;
};

int n,m,S,T;
int Input[maxMap][maxMap];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
void _Add(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
    mem(Input,-1);mem(Head,-1);
    scanf("%d%d",&n,&m);S=n*m+1;T=n*m+2;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Input[i][j]);
    for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
	    if (Input[i][j]==2)
	    {
		Add_Edge(S,Id(i,j),inf);
		for (int k=1;k<=4;k++)
		    if ((i+F1[k]<=n)&&(i+F1[k]>=1)&&(j+F2[k]<=m)&&(j+F2[k]>=1))
			if ((Input[i+F1[k]][j+F2[k]]==0)||(Input[i+F1[k]][j+F2[k]]==1))
			    Add_Edge(Id(i,j),Id(i+F1[k],j+F2[k]),1);
	    }
	    else if (Input[i][j]==0)
	    {
		for (int k=1;k<=4;k++)
		    if ((i+F1[k]<=n)&&(i+F1[k]>=1)&&(j+F2[k]<=m)&&(j+F2[k]>=1))
			if ((Input[i+F1[k]][j+F2[k]]==0)||(Input[i+F1[k]][j+F2[k]]==1))
			    Add_Edge(Id(i,j),Id(i+F1[k],j+F2[k]),1);
	    }
	    else Add_Edge(Id(i,j),T,inf);
    int Ans=0;
    while (Bfs())
    {
	for (int i=1;i<=T;i++) cur[i]=Head[i];
	while (int di=dfs(S,inf)) Ans+=di;
    }
    printf("%d\n",Ans);
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
	    if (di>0)
	    {
		E[i].flow-=di;
		E[i^1].flow+=di;
		return di;
	    }
	}
    return 0;
}
