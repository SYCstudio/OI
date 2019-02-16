#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=301;
const int maxM=101*101*20;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Head_[maxN];
int Next[maxM];
Edge E[maxM];
Edge E2[maxM];
int cur[maxN];
int depth[maxN];
int Mayuri[maxN];
int Map[maxN][maxN];
int Q[maxN];

void Add_Edge(int u,int v,int flow);
int max_flow(int value);
bool bfs();
int dfs(int u,int flow);
int Find(int u);

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		memset(Map,0,sizeof(Map));
		int f;
		scanf("%d%d%d",&n,&m,&f);
		for (int i=1;i<=n;i++)
			Mayuri[i]=i;
		for (int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			Add_Edge(u,v+n,1);
			Map[u][v]=1;
		}
		for (int i=1;i<=f;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			int fu=Find(u);
			int fv=Find(v);
			if (fu!=fv)
			    Mayuri[fu]=fv;
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (Find(i)==Find(j))
					for (int k=1;k<=n;k++)
						if ((Map[i][k]==1)&&(Map[j][k]==0))
						{
							Map[j][k]=1;
							Add_Edge(j,k+n,1);
						}
		int l=0,r=n*n;
		int Ans;
		while (l<=r)
		{
			//cout<<l<<" "<<r<<endl;
			int mid=(l+r)/2;
			if (mid*n==max_flow(mid))
			{
				l=mid+1;
				Ans=mid;
			}
			else
				r=mid-1;
		}
		printf("%d\n",Ans);
	}
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

int max_flow(int value)
{
	int cnt_=cnt;
	for (int i=0;i<=2*n+1;i++)
		Head_[i]=Head[i];
	for (int i=0;i<=cnt;i++)
		E2[i]=E[i];
	for (int i=1;i<=n;i++)
	{
		Add_Edge(0,i,value);
		Add_Edge(i+n,n*2+1,value);
	}
	int Ans=0;
	while (bfs())
	{
		for (int i=0;i<=2*n+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	cnt=cnt_;
	for (int i=0;i<=2*n+1;i++)
		Head[i]=Head_[i];
	for (int i=0;i<=cnt;i++)
		E[i]=E2[i];
	//cout<<Ans<<endl;
	return Ans;
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
	if (depth[n*2+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n*2+1)
		return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
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

int Find(int u)
{
	if (Mayuri[u]!=u)
		Mayuri[u]=Find(Mayuri[u]);
	return Mayuri[u];
}
