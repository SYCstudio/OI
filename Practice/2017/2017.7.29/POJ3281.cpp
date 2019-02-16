#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=510;
const int maxM=2147483647;
const int inf=2147483647;

int n,F,D;
int G[maxN][maxN];
int Flow[maxN];
int Path[maxN];

bool bfs();

int main()
{
	memset(G,0,sizeof(G));
	scanf("%d%d%d",&n,&F,&D);
	for (int i=1;i<=n;i++)
		G[i][i+n]=1;
	for (int i=1;i<=n;i++)
	{
		int n1,n2;
		scanf("%d%d",&n1,&n2);
		for (int j=1;j<=n1;j++)
		{
			int v;
			scanf("%d",&v);
			G[2*n+v][i]=1;
		}
		for (int j=1;j<=n2;j++)
		{
			int v;
			scanf("%d",&v);
			G[i+n][2*n+F+v]=1;
		}
	}
	for (int i=1;i<=F;i++)
		G[0][n*2+i]=1;
	for (int i=1;i<=D;i++)
		G[n*2+F+i][n*2+F+D+1]=1;
	int Ans=0;
	while (bfs())
	{
		int di=Flow[n*2+F+D+1];
		int now=n*2+F+D+1;
		int last=Path[now];
		while (now!=0)
		{
			G[last][now]-=di;
			G[now][last]+=di;
			now=last;
			last=Path[now];
		}
		Ans++;
	}
	cout<<Ans<<endl;
	return 0;
}

bool bfs()
{
	memset(Path,-1,sizeof(Path));
	memset(Flow,0,sizeof(Flow));
	Flow[0]=inf;
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(0);
	do
	{
		int u=Q.front();
		Q.pop();
		for (int i=0;i<=2*n+F+D+1;i++)
		{
			if ((Path[i]==-1)&&(G[u][i]>0))
			{
				Path[i]=u;
				Q.push(i);
				Flow[i]=min(Flow[u],G[u][i]);
			}
		}
	}
	while (!Q.empty());
	if (Flow[n*2+F+D+1]==0)
		return 0;
	return 1;
}
