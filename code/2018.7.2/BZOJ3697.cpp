#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN*2;
const int inf=2147483647;

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int root,nowsum,MxSon[maxN],Size[maxN];
bool vis[maxN];
int St[maxN],Dist[maxN],Depth[maxN];
int Tot[maxM],F[2][maxM],Zero[maxN];
ll Ans=0;

void dfs_root(int u,int fa);
void Divide(int u);
void dfs_calc(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);if (w==0) w=-1;
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	}

	root=0;MxSon[0]=inf;nowsum=n;
	dfs_root(1,1);
	Divide(root);

	printf("%lld\n",Ans);
	return 0;
}

void dfs_root(int u,int fa)
{
	Size[u]=1;MxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa))
		{
			dfs_root(V[i],u);Size[u]+=Size[V[i]];
			MxSon[u]=max(MxSon[u],Size[V[i]]);
		}
	MxSon[u]=max(MxSon[u],nowsum-Size[u]);
	if (MxSon[u]<MxSon[root]) root=u;
	return;
}

void Divide(int u)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			St[0]=0;
			Depth[V[i]]=1;Dist[V[i]]=W[i];
			dfs_calc(V[i],u);
			for (int j=1;j<=St[0];j++)
			{
				if (Zero[St[j]]){
					Ans=Ans+F[1][-Dist[St[j]]+maxN]+F[0][-Dist[St[j]]+maxN];
				}
				else Ans=Ans+F[1][-Dist[St[j]]+maxN];
				if ((Zero[St[j]]==0)&&(Dist[St[j]]==0)) Ans=Ans+F[0][maxN];
			}
			for (int j=1;j<=St[0];j++) F[Zero[St[j]]][Dist[St[j]]+maxN]++;
		}
	Ans=Ans+F[1][maxN];

	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			St[0]=0;Dist[V[i]]=W[i];
			dfs_calc(V[i],u);
			for (int j=1;j<=St[0];j++) F[Zero[St[j]]][Dist[St[j]]+maxN]=0;
		}

	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			nowsum=Size[V[i]];root=0;
			dfs_root(V[i],V[i]);
			Divide(root);
		}
	return;
}

void dfs_calc(int u,int fa)
{
	St[++St[0]]=u;
	Zero[u]=(bool)Tot[-Dist[u]+maxN];
	Tot[-Dist[u]+maxN]++;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			Depth[V[i]]=Depth[u]+1;Dist[V[i]]=Dist[u]+W[i];
			dfs_calc(V[i],u);
		}
	Tot[-Dist[u]+maxN]--;
	return;
}
