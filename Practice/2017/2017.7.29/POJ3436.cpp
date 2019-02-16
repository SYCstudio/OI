#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=200;
const int maxP=30;
const int inf=2147483647;

class Edge
{
public:
	int u,v,w;
};

int n,m,P;
int G[maxN][maxN];
int G2[maxN][maxN];
int W[maxN];
int In[maxN][maxP];
int Out[maxN][maxP];
int Path[maxN];
int Flow[maxN];
Edge Outp[maxN*maxN];

bool bfs();

int main()
{
	memset(G,0,sizeof(G));
	scanf("%d%d",&P,&n);
	for (int i=1;i<=n;i++)//输入
	{
		scanf("%d",&W[i]);
		for (int j=1;j<=P;j++)
			scanf("%d",&In[i][j]);
		for (int j=1;j<=P;j++)
			scanf("%d",&Out[i][j]);
	}
	for (int i=1;i<=n;i++)//给每个点的入点到出点连一条边
		G[i][i+n]=W[i];
	for (int i=1;i<=n;i++)//给每对出口与入口相对应的点连一条边
		for (int j=1;j<=n;j++)
		{
			bool ok=1;
			for (int k=1;k<=P;k++)
				if (((Out[i][k]==1)&&(In[j][k]==0))||((Out[i][k]==0)&&(In[j][k]==1)))
				{
					ok=0;
					break;
				}
			if (ok)
				G[i+n][j]=min(W[i],W[j]);
		}
	for (int i=1;i<=n;i++)//判断能否和汇点或源点连接
	{
		bool ok=1;
		for (int j=1;j<=P;j++)
			if (In[i][j]==1)
			{
				ok=0;
				break;
			}
		if (ok)
			G[0][i]=inf;
		ok=1;
		for (int j=1;j<=P;j++)
			if (Out[i][j]==0)
			{
				ok=0;
				break;
			}
		if (ok)
			G[i+n][n*2+1]=inf;
	}
	memcpy(G2,G,sizeof(G2));//把G存起来，备份一边，方便后面输出答案
	int Ans=0;
	while (bfs())//EK
	{
		int di=Flow[n*2+1];
		int now=2*n+1;
		int last=Path[now];
		while (now!=0)
		{
			G[last][now]-=di;
			G[now][last]+=di;
			now=last;
			last=Path[now];
		}
		Ans+=di;
	}
	printf("%d ",Ans);
	int top=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (G2[i+n][j]>G[i+n][j])
			{
				top++;
				Outp[top].u=i;
				Outp[top].v=j;
				Outp[top].w=G2[i+n][j]-G[i+n][j];
			}
	printf("%d\n",top);
	for (int i=1;i<=top;i++)
		printf("%d %d %d\n",Outp[i].u,Outp[i].v,Outp[i].w);
	return 0;
}

bool bfs()
{
	memset(Path,-1,sizeof(Path));
	memset(Flow,0,sizeof(Flow));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(0);
	Flow[0]=inf;
	do
	{
		int u=Q.front();
		Q.pop();
		for (int i=0;i<=2*n+1;i++)
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
	if (Flow[2*n+1]>0)
		return 1;
	return 0;
}
