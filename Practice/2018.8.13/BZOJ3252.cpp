#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Val[maxN];
int Depth[maxN],Hson[maxN],Fa[maxN];
int lcnt=0;
ll Sum[maxN],MxD[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,ll sum);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%lld",&Val[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Depth[1]=1;
	dfs1(1,1);dfs2(1,0);

	sort(&Sum[1],&Sum[lcnt+1]);

	ll Ans=0;
	for (int i=lcnt,j=1;(i>=1)&&(j<=K);i--,j++) Ans+=Sum[i];

	printf("%lld\n",Ans);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	MxD[u]=Val[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Fa[V[i]]=u;
			dfs1(V[i],u);
			if (MxD[V[i]]+Val[u]>MxD[u]) Hson[u]=V[i],MxD[u]=MxD[V[i]]+Val[u];
		}
	return;
}

void dfs2(int u,ll sum){
	sum+=Val[u];
	if (Hson[u]==0){
		Sum[++lcnt]=sum;return;
	}
	dfs2(Hson[u],sum);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],0);
	return;
}
/*
5 2
4 3 2 1 1
1 2
1 5
2 3
2 4
//*/
