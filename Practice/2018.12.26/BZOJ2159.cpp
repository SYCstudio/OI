#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxN=50500;
const int maxM=maxN<<1;
const int maxK=151;
const int Mod=10007;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int F[maxN][maxK],Bp[maxK];
int S[maxK][maxK],Fac[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
int Plus(int x,int y);
int Minus(int x,int y);

int main(){
	memset(Head,-1,sizeof(Head));
	int L,now,A,B,Q,tmp;scanf("%d%d%d%d%d%d%d",&n,&K,&L,&now,&A,&B,&Q);
	for (int i=1;i<n;i++){
		now=(now*A+B)%Q;tmp=(i<L)?i:L;
		int u=i-now%tmp,v=i+1;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,0);
	/*
	for (int i=1;i<=n;i++){
		for (int j=0;j<=K;j++) cout<<F[i][j]<<" ";cout<<endl;
	}
	//*/
	dfs2(1,0);
	S[0][0]=1;Fac[0]=1;for (int i=1;i<=K;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	for (int i=1;i<=K;i++) for (int j=1;j<=i;j++) S[i][j]=(S[i-1][j-1]+1ll*j*S[i-1][j]%Mod)%Mod;
	for (int i=1;i<=n;i++){
		int sum=0;
		for (int j=1;j<=K;j++) sum=(sum+1ll*S[K][j]*Fac[j]%Mod*F[i][j]%Mod)%Mod;
		printf("%d\n",sum);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	F[u][0]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];dfs1(v,u);
			F[u][0]=Plus(F[u][0],F[v][0]);
			for (int j=1;j<=K;j++) F[u][j]=Plus(Plus(F[u][j],F[v][j-1]),F[v][j]);
		}
	return;
}

void dfs2(int u,int fa){
	if (fa!=0){
		for (int i=0;i<=K;i++) Bp[i]=F[fa][i];
		Bp[0]=Minus(Bp[0],F[u][0]);
		for (int i=1;i<=K;i++) Bp[i]=Minus(Minus(Bp[i],F[u][i]),F[u][i-1]);
		F[u][0]=Plus(F[u][0],Bp[0]);
		for (int i=1;i<=K;i++) F[u][i]=Plus(Plus(F[u][i],Bp[i-1]),Bp[i]);
	}
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) dfs2(V[i],u);
	return;
}

int Plus(int x,int y){
	x+=y;if (x>=Mod) x-=Mod;
	return x;
}

int Minus(int x,int y){
	x-=y;if (x<0) x+=Mod;
	return x;
}
