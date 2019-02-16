#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100*2;
const int maxM=1010000;
const int inf=2147483647;

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Ans=0;
int dfncnt,dfn[maxN],low[maxN],FaW[maxN];
int Seq[maxN];
int F[maxN],G[maxN];
int Q[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void RingDp(int tp,int bt);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int K;scanf("%d",&K);
		int u;scanf("%d",&u);K--;
		while (K--){
			int v;scanf("%d",&v);
			Add_Edge(u,v);u=v;
		}
	}

	/*
	for (int i=1;i<=n;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<" -> "<<V[j]<<endl;
	//*/

	tarjan(1,edgecnt+2);

	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int faw)
{
	//cout<<"tarjan:"<<u<<endl;
	dfn[u]=low[u]=++dfncnt;F[u]=0;FaW[u]=faw;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((i!=faw)&&((i^1)!=faw))
		{
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,i);low[u]=min(low[u],low[v]);
				if (low[v]>dfn[u]){
					//cout<<u<<" <- "<<v<<":"<<F[u]<<" "<<F[v]<<endl;
					Ans=max(Ans,F[u]+F[v]+1);
					F[u]=max(F[u],F[v]+1);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((i!=faw)&&((i^1)!=faw)&&(dfn[V[i]]>dfn[u])&&(FaW[V[i]]!=i)&&((FaW[V[i]]^1)!=i))
			RingDp(u,V[i]);
	//cout<<u<<":"<<F[u]<<endl;
	Ans=max(Ans,F[u]);
	return;
}

void RingDp(int tp,int bt)
{
	//cout<<"ringDP:"<<tp<<" "<<bt<<endl;
	int ncnt=0;
	for (int now=bt;now!=tp;now=V[FaW[now]^1]) Seq[++ncnt]=now;
	Seq[++ncnt]=tp;
	//cout<<"Seq:";for (int i=1;i<=ncnt;i++) cout<<Seq[i]<<" ";cout<<endl;

	for (int i=ncnt+1;i<=ncnt+ncnt;i++) Seq[i]=Seq[i-ncnt];

	int len=ncnt/2;
	int l=1,r=1;Q[1]=1;
	for (int i=2;i<=ncnt+ncnt;i++)
	{
		while ((l<=r)&&(Q[l]+len<i)) l++;
		if (l<=r){
			//cout<<Q[l]<<" "<<i<<" ["<<Seq[Q[l]]<<" "<<Seq[i]<<"] "<<F[Seq[Q[l]]]+F[Seq[i]]+i-Q[l]<<endl;
			Ans=max(Ans,F[Seq[Q[l]]]+F[Seq[i]]+i-Q[l]);
		}
		while ((l<=r)&&(F[Seq[Q[r]]]+i-Q[r]<=F[Seq[i]])) r--;
		Q[++r]=i;
	}

	for (int i=1;i<ncnt;i++){
		//cout<<Seq[i]<<":"<<F[Seq[i]]<<" "<<i<<" "<<ncnt-i<<endl;
		F[tp]=max(F[tp],F[Seq[i]]+min(i,ncnt-i));
	}
	return;
}
