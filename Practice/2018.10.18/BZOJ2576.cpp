#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=110;
const int maxK=19;
const int inf=2147483647;

int n,m,K;
int Id[maxN],Seq[maxN];
bool Mat[maxN][maxN],Link[maxK+5][maxK+5];
ll F[(1<<maxK)+10][maxK+1];
int G[(1<<maxK)+10][maxK+1];

int dfs(RG int u,RG int S);
ll dp(RG int u,RG int S);

int main(){
	int i,u,v,j;
	scanf("%d%d%d",&n,&m,&K);++K;
	for (i=1;i<=m;++i){
		scanf("%d%d",&u,&v);
		Mat[u][v]=Mat[v][u]=1;
	}
	for (i=1;i<=n;++i) Id[i]=K;
	for (i=0;i<K-1;++i){
		scanf("%d",&Seq[i]);
		Id[Seq[i]]=i;Link[i][K-1]=Link[K-1][i]=1;
	}
	for (i=0;i<=K;++i)
		for (j=1;j<=n;++j)
			Link[i][Id[j]]|=Mat[Seq[i]][j];
	mem(G,-1);mem(F,-1);
	for (i=0;i<(1<<K);++i) for (j=0;j<K;++j) if (i>>j&1) dfs(j,i);
	printf("%lld\n",dp(K-1,1<<(K-1)));return 0;
}

int dfs(RG int u,RG int S){
	if (~G[S][u]) return G[S][u];
	RG int ret=1<<u;//G[S][u]=1<<u;
	for (RG int i=0;i<K;++i)
		if (Link[u][i]&&!(S>>i&1))
			ret|=dfs(i,S|(1<<i));
	return G[S][u]=ret;
}

ll dp(RG int u,RG int S){
	if (~F[S][u]) return F[S][u];
	if (G[S][u]==1<<u){
		return S==(1<<K)-1||!Link[u][K];
	}
	RG ll ret=0;
	for (RG int i=0;i<K;++i)
		if (Link[u][i]&&!(S>>i&1))
			ret+=dp(i,S| 1<<i )*dp(u,S|G[S|1<<i][i]);
	return F[S][u]=ret;
}
/*
8 7 5
1 2
1 3
1 6
3 4
2 5
7 8 
8 7
1 2 3 7 8
//*/
