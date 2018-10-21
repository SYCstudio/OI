#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxM=60100<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN];
int F[maxN][2],G[maxN][2],Fa[maxN];
int Seq[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void RingDp(int tp,int bt);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	tarjan(1,1);

	printf("%d\n",max(F[1][0],F[1][1]));

	return 0;
}

void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;Fa[u]=fa;F[u][1]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			if (dfn[V[i]]==0){
				tarjan(V[i],u);
				low[u]=min(low[u],low[V[i]]);
				if (low[V[i]]>dfn[u]){
					F[u][0]+=max(F[V[i]][0],F[V[i]][1]);
					F[u][1]+=F[V[i]][0];
				}
			}
			else low[u]=min(low[u],dfn[V[i]]);
		}
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(Fa[V[i]]!=u)&&(dfn[V[i]]>dfn[u]))
			RingDp(u,V[i]);
	return;
}

void RingDp(int tp,int bt)
{
	//cout<<"ringDP:"<<tp<<" "<<bt<<endl;
	int ncnt=0;
	for (int now=bt;now!=tp;now=Fa[now]) Seq[++ncnt]=now;
	Seq[++ncnt]=tp;

	//for (int i=1;i<=ncnt;i++) cout<<Seq[i]<<" ";cout<<endl;

	//强制不选择bt
	G[bt][1]=-inf;G[bt][0]=F[bt][0];
	for (int i=2;i<=ncnt;i++)
	{
		G[Seq[i]][0]=F[Seq[i]][0]+max(G[Seq[i-1]][0],G[Seq[i-1]][1]);
		G[Seq[i]][1]=F[Seq[i]][1]+G[Seq[i-1]][0];
	}
	//cout<<"Dp1:"<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][0]<<" ";cout<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][1]<<" ";cout<<endl;

	int mx0=G[tp][0],mx1=G[tp][1];

	//强制不选择tp
	G[bt][1]=F[bt][1];G[bt][0]=F[bt][0];
	for (int i=2;i<=ncnt;i++)
	{
		G[Seq[i]][0]=F[Seq[i]][0]+max(G[Seq[i-1]][0],G[Seq[i-1]][1]);
		G[Seq[i]][1]=F[Seq[i]][1]+G[Seq[i-1]][0];
	}
	mx0=max(G[tp][0],mx0);
	//cout<<"Dp2:"<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][0]<<" ";cout<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<G[Seq[i]][1]<<" ";cout<<endl;

	F[tp][0]=max(F[tp][0],mx0);F[tp][1]=max(F[tp][1],mx1);
	return;
}
