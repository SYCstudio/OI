#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000;
const int maxM=maxN*maxN*4;
const int inf=147483647;

class Edge
{
public:
	int u,v,flow;
};

int n;
int cnt=-1;
int F[maxN];
int Arr[maxN];
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
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&Arr[i]);
	for (int i=1;i<=n;i++)
	{
		F[i]=1;
		for (int j=1;j<i;j++)
		    if (Arr[j]<=Arr[i])
				F[i]=max(F[i],F[j]+1);
	}
	int maxlength=1;
	for (int i=1;i<=n;i++)
		maxlength=max(maxlength,F[i]);
	printf("%d\n",maxlength);
	memset(Head,-1,sizeof(Head));
	for (int i=1;i<=n;i++)
	{
		Add_Edge(i,i+n,1);
		if (F[i]==maxlength)
			Add_Edge(0,i,1);
		if (F[i]==1)
			Add_Edge(i+n,n*2+1,1);
		for (int j=1;j<i;j++)
			if ((F[j]==F[i]-1)&&(Arr[j]<=Arr[i]))
				Add_Edge(i+n,j,1);
	}
	int Ans=0;
	while (bfs())
	{
		for (int i=0;i<=2*n+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	cout<<Ans<<endl;
	memset(Head,-1,sizeof(Head));
	cnt=-1;
	for (int i=1;i<=n;i++)
	{
		int nowflow=1;
		if ((i==1)||(i==n))
			nowflow=inf;
        if (maxlength==1)
            Add_Edge(i,i+n,1);
        else
            Add_Edge(i,i+n,inf);
		if (F[i]==maxlength)
			Add_Edge(0,i,nowflow);
		if (F[i]==1)
			Add_Edge(i+n,n*2+1,nowflow);
		for (int j=1;j<i;j++)
			if ((F[j]==F[i]-1)&&(Arr[j]<=Arr[i]))
				Add_Edge(i+n,j,1);
	}
	Ans=0;
	/*for (int i=0;i<=n*2+1;i++)
	{
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<" "<<E[j].v<<" "<<E[j].flow<<endl;
		cout<<endl;
		}*/
	while (bfs())
	{
		for (int i=0;i<=2*n+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	cout<<Ans<<endl;
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
	E[cnt].v=u;
	E[cnt].u=v;
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
		//cout<<u<<endl;
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
	while (t!=h);
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
