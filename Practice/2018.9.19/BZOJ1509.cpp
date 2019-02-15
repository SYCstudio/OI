#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
ll F[3][maxN],G[3][maxN];

void Add_Edge(int u,int v,int w);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
void Update(int u,int v,ll w);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}

	dfs1(1,1);
	dfs2(1,1);

	//for (int i=1;i<=n;i++) cout<<F[0][i]<<" "<<F[1][i]<<" "<<F[2][i]<<" , "<<G[0][i]<<" "<<G[1][i]<<" "<<G[2][i]<<endl;

	ll Ans=0;
	for (int i=1;i<=n;i++) Ans=max(Ans,F[0][i]+2*F[1][i]+F[2][i])/*,cout<<F[0][i]<<" "<<2*F[1][i]<<" "<<F[2][i]<<endl*/;

	printf("%lld\n",Ans);return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs1(int u,int fa){
	F[0][u]=F[1][u]=F[2][u]=0;G[0][u]=G[1][u]=G[2][u]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs1(V[i],u);
			Update(u,V[i],W[i]);
		}
	return;
}

void dfs2(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Update(V[i],u,W[i]);
			dfs2(V[i],u);
		}
	return;
}

void Update(int u,int v,ll w){
	int d=-inf;
	if (G[0][v]!=u) d=F[0][v];
	else if (G[1][v]!=u) d=F[1][v];
	else if (G[2][v]!=u) d=F[2][v];
	//cout<<"Update:"<<u<<" "<<v<<" "<<d<<endl;
	if (d+w>=F[0][u]){
		F[2][u]=F[1][u];G[2][u]=G[1][u];
		F[1][u]=F[0][u];G[1][u]=G[0][u];
		F[0][u]=d+w;G[0][u]=v;
	}
	else if (d+w>=F[1][u]){
		F[2][u]=F[1][u];G[2][u]=G[1][u];
		F[1][u]=d+w;G[1][u]=v;
	}
	else if (d+w>F[2][u]){
		F[2][u]=d+w;G[2][u]=v;
	}
	return;
}
