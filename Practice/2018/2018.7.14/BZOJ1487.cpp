#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=201000<<1;
const int inf=2147483647;

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Val[maxN];
int dfncnt,dfn[maxN],low[maxN],Fa[maxN];
int F[maxN][2],G[maxN][2],Seq[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void RingDp(int tp,int bt);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);

	tarjan(1,1);

	printf("%d\n",max(F[1][0],F[1][1]));

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int fa)
{
	//cout<<"tarjan:"<<u<<endl;
	dfn[u]=low[u]=++dfncnt;Fa[u]=fa;F[u][1]=Val[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if (low[v]>dfn[u]){
					F[u][0]=F[u][0]+max(F[v][0],F[v][1]);
					F[u][1]=F[u][1]+F[v][0];
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}

	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(Fa[V[i]]!=u)&&(dfn[V[i]]>dfn[u]))
			RingDp(u,V[i]);

	//cout<<u<<":"<<F[u][0]<<" "<<F[u][1]<<endl;
	
	return;
}

void RingDp(int tp,int bt)
{
	//cout<<"RingDp:"<<tp<<" "<<bt<<endl;
	int ncnt=0;
	for (int now=bt;now!=tp;now=Fa[now]) Seq[++ncnt]=now;
	Seq[++ncnt]=tp;

	//强制不选bt
	G[bt][0]=F[bt][0];G[bt][1]=-inf;
	for (int i=2;i<=ncnt;i++)
	{
		G[Seq[i]][0]=F[Seq[i]][0]+max(G[Seq[i-1]][0],G[Seq[i-1]][1]);
		G[Seq[i]][1]=F[Seq[i]][1]+G[Seq[i-1]][0];
	}
	int mx0=G[tp][0],mx1=G[tp][1];
	//cout<<"Dp1:"<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][0]<<" ";cout<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][1]<<" ";cout<<endl;

	//强制不选tp
	G[bt][0]=F[bt][0];G[bt][1]=F[bt][1];
	for (int i=2;i<=ncnt;i++)
	{
		G[Seq[i]][0]=F[Seq[i]][0]+max(G[Seq[i-1]][0],G[Seq[i-1]][1]);
		G[Seq[i]][1]=F[Seq[i]][1]+G[Seq[i-1]][0];
	}
	mx0=max(mx0,G[tp][0]);
	//cout<<"Dp2:"<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][0]<<" ";cout<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][1]<<" ";cout<<endl;

	F[tp][0]=max(mx0,F[tp][0]);F[tp][1]=max(mx1,F[tp][1]);
	return;
}	
