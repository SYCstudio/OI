#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxM=maxN<<1;
const int maxW=4110;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Mx[maxN],Fa[maxN],root,nowsize;
int NW[maxN],C[maxN],D[maxN];
int F[maxN][maxW],G[maxW];
bool vis[maxN];
int Ans=0;

void Add_Edge(int u,int v);
void GetRoot(int u,int fa);
void Solve(int u);
void dp(int u,int fa);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&n,&m);edgecnt=Ans=0;mem(Head,-1);mem(vis,0);
		for (int i=1;i<=n;i++) scanf("%d",&NW[i]);
		for (int i=1;i<=n;i++) scanf("%d",&C[i]);
		for (int i=1;i<=n;i++) scanf("%d",&D[i]);
		for (int i=1;i<n;i++){
			int u,v;scanf("%d%d",&u,&v);
			Add_Edge(u,v);Add_Edge(v,u);
		}

		Mx[0]=inf;root=0;nowsize=n;
		GetRoot(1,1);
		Solve(root);

		printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void GetRoot(int u,int fa){
	Size[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Fa[V[i]]=u;GetRoot(V[i],u);
			Mx[u]=max(Mx[u],Size[V[i]]);Size[u]+=Size[V[i]];
		}
	Mx[u]=max(Mx[u],nowsize-Size[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

void Solve(int u){
	vis[u]=1;
	dp(u,u);
	for (int i=1;i<=m;i++) Ans=max(Ans,F[u][i]);
	for (int i=Head[u],sz=nowsize;i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			root=0;nowsize=Size[V[i]];
			GetRoot(V[i],V[i]);
			Solve(root);
		}
	return;
}

void dp(int u,int fa){
	for (int i=0;i<=m;i++) F[u][i]=0;
	for (int i=1,s=C[u];(i<=D[u])&&(s<=m);i++,s+=C[u]) F[u][s]=i*NW[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			int v=V[i];dp(v,u);
			for (int j=1;j<=m;j++) G[j]=0;
			for (int s1=C[u];s1<=m;s1++)
				for (int s2=C[v];s1+s2<=m;s2++)
					G[s1+s2]=max(G[s1+s2],F[u][s1]+F[v][s2]);
			for (int j=1;j<=m;j++) F[u][j]=max(F[u][j],G[j]);
		}
	return;
}

/*
1
3 2
1 2 3
1 1 1
1 2 1
1 2
1 3
//*/
