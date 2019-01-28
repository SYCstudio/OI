#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define RG register

const int maxN=21;
const int Mod=998244353;

int n,m,N,P,inv2;
int D[maxN+1],ufs[maxN+1],Ls[maxN+1];
int W[1<<maxN],Bc[1<<maxN],Iw[1<<maxN],f[maxN+1][1<<maxN],dp[maxN+1][1<<maxN];

int QPow(int x,int cnt);
int find(int x);
bool check(int S);
void FWT(int *P,int len,int opt);
int Plus(int x,int y);
int Minus(int x,int y);

int main(){
	//freopen("14.in","r",stdin);
	scanf("%d%d%d",&n,&m,&P);N=1<<n;inv2=QPow(2,Mod-2);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);--u;--v;
		Ls[u]|=(1<<v);Ls[v]|=(1<<u);
	}
	for (int i=0;i<n;i++) scanf("%d",&W[1<<i]);
	for (int i=1;i<N;i++) Bc[i]=Bc[i>>1]+(i&1);
	for (int i=1;i<N;i++) if (Bc[i]>=2) W[i]=W[i&(i-1)]+W[i^(i&(i-1))];
	for (int i=0;i<N;i++) Iw[i]=QPow(QPow(W[i],P),Mod-2);
	for (int i=1;i<N;i++) if (check(i)) f[Bc[i]][i]=QPow(W[i],P);
	
	for (int i=1;i<=n;i++) FWT(f[i],N,1);
	
	for (int i=1;i<=n;i++) for (int j=0;j<N;j++) dp[i][j]=f[i][j];
	for (int i=1;i<=n;i++){
		for (int j=1;j<i;j++) for (int k=0;k<N;k++) dp[i][k]=(dp[i][k]+1ll*dp[j][k]*f[i-j][k]%Mod)%Mod;
		FWT(dp[i],N,-1);
		for (int k=0;k<N;k++) dp[i][k]=1ll*dp[i][k]*Iw[k]%Mod;
		for (int k=0;k<N;k++) if (Bc[k]!=i) dp[i][k]=0;
		if (i!=n) FWT(dp[i],N,1);
	}
	
	printf("%d\n",dp[n][N-1]);return 0;
}
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
int find(int x){
	if (ufs[x]!=x) ufs[x]=find(ufs[x]);
	return ufs[x];
}
bool check(int S){
	for (int i=1;i<=n;i++) D[i]=0,ufs[i]=i;
	for (int i=0;i<n;i++)
		if (S&(1<<i)){
			int nS=S&Ls[i];D[i+1]=Bc[nS];
			for (int j=0;j<n;j++) if (nS&(1<<j)) ufs[find(j+1)]=find(i+1);
		}
	for (int i=1,lst=-1;i<=n;i++)
		if ((S>>(i-1))&1){
			if (lst!=-1) if (lst!=find(i)) return 1;
			lst=find(i);
		}
	for (int i=1;i<=n;i++) if (D[i]&1) return 1;
	return 0;
}
void FWT(int *P,int len,int opt){
	for (int i=1;i<len;i<<=1)
		for (int j=0,l=i<<1;j<len;j+=l)
			for (int k=0;k<i;k++){
				int X=P[j+k],Y=P[j+k+i];
				if (opt==1) P[j+k+i]=Plus(X,Y);
				else P[j+k+i]=Minus(Y,X);
			}
	return;
}
inline int Plus(RG int x,RG int y){
	x+=y;if (x>=Mod) x-=Mod;return x;
}
inline int Minus(RG int x,RG int y){
	x-=y;if (x<0) x+=Mod;return x;
}
