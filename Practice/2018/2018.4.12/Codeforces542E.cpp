#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=101000*2;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Belong[maxN],gcnt=0;
int Col[maxN];
int Ans[maxN];
bool oddring;
int Depth[maxN],Queue[maxN];

void Add_Edge(int u,int v);
void dfs(int u);
void Bfs(int S);

int main()
{
	mem(Head,-1);mem(Col,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++)
		if (Belong[i]==0)
		{
			gcnt++;Col[i]=0;
			dfs(i);
		}
	if (oddring)
	{
		cout<<-1<<endl;
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		Bfs(i);
		for (int j=1;j<=n;j++) Ans[Belong[i]]=max(Ans[Belong[i]],Depth[j]);
	}
	int sum=0;
	for (int i=1;i<=gcnt;i++) sum+=Ans[i];
	cout<<sum<<endl;
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u)
{
	Belong[u]=gcnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Col[V[i]]==-1)
		{
			Col[V[i]]=Col[u]^1;
			dfs(V[i]);
		}
		else if (Col[V[i]]==Col[u]) oddring=1;
	return;
}

void Bfs(int S)
{
	mem(Depth,-1);
	int h=1,t=0;Queue[1]=S;Depth[S]=0;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Depth[V[i]]==-1)
				Depth[Queue[++h]=V[i]]=Depth[u]+1;
	}
	while (t!=h);
	return;
}
