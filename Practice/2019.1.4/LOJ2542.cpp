#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=18;
const int maxM=maxN<<1;
const int Mod=998244353;

int n,Q,rt;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],D[maxN];
int A[maxN],B[maxN],F[maxN][1<<maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa,int S);
void dfs2(int u,int fa,int S);
int Plus(int x,int y);
int QPow(int x,int cnt);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	mem(Head,-1);
	scanf("%d%d%d",&n,&Q,&rt);
	--rt;
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		--u;
		--v;
		Add_Edge(u,v);
		Add_Edge(v,u);
		++D[u];
		++D[v];
	}
	for (int S=1; S<(1<<n); S++) {
		mem(A,0);
		mem(B,0);
		dfs1(rt,rt,S);
		dfs2(rt,rt,S);
		//cout<<S<<endl;
		//for (int i=0;i<n;i++) cout<<A[i]<<" ";cout<<endl;
		//for (int i=0;i<n;i++) cout<<B[i]<<" ";cout<<endl;
		//for (int i=0;i<n;i++) cout<<F[i][S]<<" ";cout<<endl;
	}
	while (Q--) {
		int k,S=0;
		scanf("%d",&k);
		while (k--) {
			int u;
			scanf("%d",&u);
			--u;
			S|=(1<<u);
		}
		printf("%d\n",F[rt][S]);
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs1(int u,int fa,int S)
{
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) dfs1(V[i],u,S);
	if ((S>>u)&1) {
		if ((S^(1<<u))==0) A[u]=B[u]=0;
		else {
			A[u]=B[u]=0;
			for (int i=Head[u]; i!=-1; i=Next[i])
				B[u]=Plus(B[u],F[V[i]][S^(1<<u)]);
			B[u]=(1ll*B[u]*QPow(D[u],Mod-2)+1)%Mod;
		}
	} else {
		int sa=0,sb=0;
		for (int i=Head[u]; i!=-1; i=Next[i])
			if (V[i]!=fa) sa=Plus(sa,A[V[i]]),sb=Plus(sb,B[V[i]]);
		//cout<<u<<" "<<sa<<" "<<sb<<endl;
		A[u]=QPow(((D[u]-sa)%Mod+Mod)%Mod,Mod-2);
		B[u]=1ll*(D[u]+sb)%Mod*A[u]%Mod;
		if (u==fa) A[u]=0;
		//cout<<A[u]<<" "<<B[u]<<endl;
	}
	return;
}
void dfs2(int u,int fa,int S)
{
	if (u==rt) F[u][S]=B[u];
	else F[u][S]=(1ll*A[u]*F[fa][S]%Mod+B[u])%Mod;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) dfs2(V[i],u,S);
	return;
}
int Plus(int x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return x;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
