#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Size[maxN],F[maxN],G[maxN];
ll Ans=0,sf=0;

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<Size[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;
	Ans=(Ans+sf/2)/2;
	printf("%lld\n",Ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	G[u]=1;Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			F[u]+=G[V[i]];G[u]+=F[V[i]];
		}
	return;
}

void dfs2(int u,int fa){
	Ans=Ans+1ll*Size[u]*(n-Size[u]);sf+=F[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			F[V[i]]+=G[u]-F[V[i]];
			G[V[i]]+=F[u]-G[V[i]];
			dfs2(V[i],u);
		}
	return;
}
