#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000*8;
const int Mod=924844033;
const int inf=2147483647;

int n,N,L,G,Fac[maxN],InvF[maxN];
int edgecnt=0,Head[maxN],Next[maxN],V[maxN],Sz[maxN],Cnt[maxN];
int A[maxN],B[maxN],Rader[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);
int QPow(int x,int cnt,int M);
int GetG(int x);
void NTT(int *P,int opt);

int main(){
	Fac[0]=InvF[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	InvF[maxN-1]=QPow(Fac[maxN-1],Mod-2,Mod);for (int i=maxN-2;i>=1;i--) InvF[i]=1ll*InvF[i+1]*(i+1)%Mod;
	G=GetG(Mod);mem(Head,-1);
	scanf("%d",&n);for (N=1;N<=(n+n);N<<=1) ++L;for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs(1,1);
	for (int i=1;i<=n;i++) A[i]=1ll*Cnt[i]*Fac[i]%Mod;
	for (int i=0;i<=n;i++) B[i]=InvF[i];
    /*
	for (int i=1;i<=n;i++) cout<<Cnt[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	//*/
	reverse(&B[0],&B[n+1]);
	NTT(A,1);NTT(B,1);for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;NTT(A,-1);
	for (int i=1,mul=1;i<=n;i++) printf("%lld\n",(1ll*Fac[n]*InvF[n-i]%Mod*InvF[i]%Mod*n%Mod-1ll*InvF[i]*A[i+n]%Mod+Mod)%Mod);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa){
	Sz[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs(V[i],u);Sz[u]+=Sz[V[i]];++Cnt[Sz[V[i]]];
		}
	if (Sz[u]!=n) ++Cnt[n-Sz[u]];return;
}

int QPow(int x,int cnt,int M){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%M;
		x=1ll*x*x%M;cnt>>=1;
	}
	return ret;
}

int GetG(int x){
	int pcnt=0,P[50],k=x-1;
	for (int i=2;1ll*i*i<=k;i++)
		if (k%i==0){
			P[++pcnt]=i;while (k%i==0) k/=i;
		}
	for (int i=2;i;i++){
		bool flag=1;
		for (int j=1;(j<=pcnt)&&(flag);j++) if (QPow(i,(x-1)/P[j],x)==1) flag=0;
		if (flag) return i;
	}
}

void NTT(int *P,int opt){
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1),Mod);
		if (opt==-1) dw=QPow(dw,Mod-2,Mod);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2,Mod);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
