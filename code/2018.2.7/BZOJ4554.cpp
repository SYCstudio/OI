#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=52;
const int maxN=maxMap*maxMap*2;
const int maxM=maxN*20;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m,S,T;
char Input[maxMap][maxMap];
int Idx[maxMap][maxMap],Idy[maxMap][maxMap];
int nodecnt=0,edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
bool Con[maxN];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (Input[i][j]=='#')
			{
				Idx[i][j]=-1;
				continue;
			}
			if ((j==1)||(Input[i][j-1]=='#'))
			{
				Idx[i][j]=++nodecnt;
				continue;
			}
			Idx[i][j]=nodecnt;
		}
	for (int j=1;j<=m;j++)
		for (int i=1;i<=n;i++)
		{
			if (Input[i][j]=='#')
			{
				Idy[i][j]=-1;
				continue;
			}
			if ((i==1)||(Input[i-1][j]=='#'))
			{
				Idy[i][j]=++nodecnt;
				continue;
			}
			Idy[i][j]=nodecnt;
		}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++) cout<<Idx[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++) cout<<Idy[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	//*/
	S=nodecnt+1;T=nodecnt+2;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (Input[i][j]=='#') continue;
			if (Input[i][j]=='*') Add_Edge(Idx[i][j],Idy[i][j],1);
			if (Input[i][j]=='*')
			{
				if (Con[Idx[i][j]]==0)
				{
					Con[Idx[i][j]]=1;
					Add_Edge(S,Idx[i][j],1);
				}
				if (Con[Idy[i][j]]==0)
				{
					Con[Idy[i][j]]=1;
					Add_Edge(Idy[i][j],T,1);
				}
			}
		}
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
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=0;
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
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
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
