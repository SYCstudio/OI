#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxN=5000;
const int maxM=100001;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxM];
bool vis[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	int sum;
	memset(Head,-1,sizeof(Head));
	scanf("%d",&sum);
	int Ans=0;
	n=0;
	do
	{
		n++;
		Ans++;
		Add_Edge(0,n*2,1);
		Add_Edge(n*2+1,1,1);
		for (int i=1;i<n;i++)
			if (sqrt(n+i)==(int)(sqrt(n+i)))
				Add_Edge(i*2,n*2+1,1);
		while (bfs())
		{
			for (int i=0;i<=n*2+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
				Ans-=di;
		}
		/*cout<<"n:"<<n<<endl;
		for (int i=0;i<=n*2+1;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<i<<' '<<E[j].v<<' '<<E[j].flow<<endl;
			cout<<endl;
		}
		cout<<"Ans:"<<Ans<<endl;
		getchar();*/
		if (Ans>sum)
		{
			n--;
			break;
		}
	}
	while (1);
	cout<<n<<endl;
	for (int i=0;i<=cnt;i++)
		if ((E[i].u<E[i].v)||(E[i].v==1))
			E[i].flow=1;
		else
			E[i].flow=0;
	Ans=0;
	while (bfs())
	{
		for (int i=0;i<=n*2+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++)
	{
		if (vis[i]==1)
			continue;
		int now=i;
		bool get=0;
		do
		{
			cout<<now<<' ';
			vis[now]=1;
			get=0;
			for (int i=Head[now*2];i!=-1;i=Next[i])
				if ((E[i].v%2!=0)&&(E[i].flow==0))
				{
					get=1;
					now=E[i].v/2;
					break;
				}
		}
		while (get==1);
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
	if (depth[1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==1)
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
