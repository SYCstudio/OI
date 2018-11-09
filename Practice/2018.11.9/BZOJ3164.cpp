#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxM=maxN;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int F[maxN],Mk[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int opt);
void cov(int u,int opt);
//void dfs2(int u,int opt);
//void cov2(int u,int opt);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=2;i<=n;i++){
		int fa;scanf("%d",&fa);
		Add_Edge(fa,i);
	}
	dfs(1,1);cov(1,1);
	dfs(1,0);cov(1,0);
	int id=0,cnt=0,sum=0;
	for (int i=n;i>=1;i--) if (Mk[i]==2) id=i,++cnt,sum^=i;
	printf("%d %d %d\n",id,cnt,sum);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int opt){
	if (Head[u]==-1){
		F[u]=1;return;
	}
	if (opt) F[u]=inf;
	else F[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i]){
		dfs(V[i],opt^1);
		if (opt) F[u]=min(F[u],F[V[i]]);
		else F[u]+=F[V[i]];
	}
	return;
}

void cov(int u,int opt){
	if (Head[u]==-1){
		++Mk[u];return;
	}
	if (opt) for (int i=Head[u];i!=-1;i=Next[i]) if (F[V[i]]==F[u]) cov(V[i],opt^1); else;
	else for (int i=Head[u];i!=-1;i=Next[i]) cov(V[i],opt^1);
	return;
}
