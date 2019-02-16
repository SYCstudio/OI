#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dis[maxN],Mn[maxN],Dg[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);Dg[u]++;Dg[v]++;
	}

	dis[K]=0;dfs1(K,K);dfs2(K,K);

	//for (int i=1;i<=n;i++) cout<<dis[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Mn[i]<<" ";cout<<endl;

	int Ans=0;
	if (Dg[K]==1) printf("1\n");
	else{
		for (int i=1;i<=n;i++) if (dis[i]>=Mn[i]) Ans=Ans+2-Dg[i];
		printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	Mn[u]=inf;
	if (Dg[u]==1) Mn[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dis[V[i]]=dis[u]+1;dfs1(V[i],u);Mn[u]=min(Mn[u],Mn[V[i]]+1);
		}
	return;
}

void dfs2(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Mn[V[i]]=min(Mn[V[i]],Mn[u]+1);dfs2(V[i],u);
		}
	return;
}
