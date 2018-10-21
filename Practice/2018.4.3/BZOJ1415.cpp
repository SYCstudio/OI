#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=maxN*2;
const int inf=2147483647;

int n,m,S,T;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Queue[maxN],Dist[maxN],Degree[maxN];
int Path[maxN][maxN];
ld F[maxN][maxN];

void Add_Edge(int u,int v);
void Bfs(int st);
ld dfs(int u,int v);

int main()
{
	//ios::sync_with_stdio(false);
	mem(Head,-1);
	
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) F[i][j]=-1;
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++)
	{
		Bfs(i);
		for (int j=1;j<=n;j++)
			if (i==j) Path[i][j]=0;
			else
			{
				Path[i][j]=inf;
				for (int e=Head[j];e!=-1;e=Next[e])
					if (Dist[j]==Dist[V[e]]+1) Path[i][j]=min(Path[i][j],V[e]);
			}
	}
	printf("%.3LF\n",dfs(T,S));
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Degree[u]++;
	return;
}

void Bfs(int st)
{
	int h=1,t=0;mem(Dist,-1);Dist[st]=0;
	Queue[1]=st;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]==-1)
				Dist[Queue[++h]=V[i]]=Dist[u]+1;
	}
	while (t!=h);
	return;
}

ld dfs(int u,int v)//u-鼠，v-猫
{
	if (u==v) return F[u][v]=0;
	if ((Path[u][v]==u)||(Path[u][Path[u][v]]==u)) return F[u][v]=1;
	if (F[u][v]!=-1) return F[u][v];
	int now=Path[u][Path[u][v]];
	ld Ret=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		Ret+=dfs(V[i],now);
	Ret+=dfs(u,now);
	F[u][v]=Ret/(Degree[u]+1)+1;
	return F[u][v];
}
