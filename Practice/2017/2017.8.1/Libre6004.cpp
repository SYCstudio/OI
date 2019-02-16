#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1001;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int m,n;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxM];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	int pepsum=0;
	memset(Head,-1,sizeof(Head));
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			Add_Edge(i,j+m,1);
	for (int i=1;i<=m;i++)
	{
		int num;
		scanf("%d",&num);
		Add_Edge(0,i,num);
		pepsum+=num;
	}
	for (int i=1;i<=n;i++)
	{
		int num;
		scanf("%d",&num);
		Add_Edge(i+m,n+m+1,num);
	}
	int Ans=0;
	while (bfs())
	{
		for (int i=0;i<=n+m+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	//cout<<Ans<<endl;
	if (Ans<pepsum)
	{
		cout<<0<<endl;
		return 0;
	}
	cout<<1<<endl;
	for (int i=1;i<=m;i++)
	{
		for (int j=Head[i];j!=-1;j=Next[j])
			if ((E[j].v>=m+1)&&(E[j].v<=n+m)&&(E[j].flow==0))
				cout<<E[j].v-m<<" ";
		cout<<endl;
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].u=v;
	E[cnt].v=u;
	E[cnt].flow=0;
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int h=1,t=0;
	Q[1]=0;
	depth[0]=1;
	do
	{
		t++;
		int u=Q[t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((depth[v]==-1)&&(E[i].flow>0))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (h!=t);
	if (depth[n+m+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n+m+1)
		return flow;
	for (int & i=cur[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
		{
			int di=dfs(v,min(flow,E[i].flow));
			if (di>0)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	}
	return 0;
}
