#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
#define pb push_back
const int Mod=998244353;
const int g=3;
const int maxN=101000*8;

int n,Y,OPT;
int Fc[maxN],Ifc[maxN];

int QPow(int x,int cnt);
namespace Iliya{
    set<int> T1[maxN];
    int ufs[maxN];
    int main();
    int ufs_find(int x);
}
namespace Kerubiel{
    vector<int> T[maxN];
    int F[maxN],G[maxN],BASE;
    int main();
    void dfs(int u,int fa);
}
namespace Mayuri{
    int Ra[maxN],F[maxN],G[maxN];
    int I1[maxN],I2[maxN],L1[maxN],L2[maxN],E1[maxN],E2[maxN];
    int main();
    void NTT(int *P,int N,int opt);
    void PolyInv(int *A,int *B,int len);
    void PolyDery(int *A,int *B,int len);
    void PolyInte(int *A,int *B,int len);
    void PolyLn(int *A,int *B,int len);
    void PolyExp(int *A,int *B,int len);
}
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxN-1]=Inv(Fc[maxN-1]);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
    scanf("%d%d%d",&n,&Y,&OPT);
    if (Y==1){
	if (OPT==0) puts("1");
	if (OPT==1) printf("%d\n",QPow(n,n-2));
	if (OPT==2) printf("%d\n",QPow(QPow(n,n-2),2));
	return 0;
    }
    if (OPT==0) Iliya::main();
    if (OPT==1) Kerubiel::main();
    if (OPT==2) Mayuri::main();
    return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
namespace Iliya{
    int main(){
	for (int i=1;i<n;i++){
	    int u,v;scanf("%d%d",&u,&v);
	    T1[u].insert(v);T1[v].insert(u);
	}
	for (int i=1;i<=n;i++) ufs[i]=i;
	for (int i=1;i<n;i++){
	    int u,v;scanf("%d%d",&u,&v);
	    if (T1[u].count(v)) ufs[ufs_find(u)]=ufs_find(v);
	}
	int bcc=0;
	for (int i=1;i<=n;i++) if (ufs_find(i)==i) ++bcc;
	printf("%d\n",QPow(Y,bcc));
	return 0;
    }
    int ufs_find(int x){
	return ufs[x]==x?x:ufs[x]=ufs_find(ufs[x]);
    }
}
namespace Kerubiel{
    int main(){
	BASE=1ll*n*Y%Mod*Inv(1-Y+Mod)%Mod;
	for (int i=1;i<n;i++){
	    int u,v;scanf("%d%d",&u,&v);
	    T[u].pb(v);T[v].pb(u);
	}
	dfs(1,0);
	int Ans=1ll*QPow((1-Y+Mod)%Mod,n)*Inv(1ll*n*n%Mod)%Mod*G[1]%Mod;
	printf("%d\n",Ans);return 0;
    }
    void dfs(int u,int fa){
	F[u]=1;G[u]=BASE;
	for (int i=0;i<T[u].size();i++){
	    int v=T[u][i];if (v==fa) continue;
	    dfs(v,u);
	    G[u]=(1ll*F[u]*G[v]%Mod+1ll*F[v]*G[u]%Mod+1ll*G[u]*G[v]%Mod)%Mod;
	    F[u]=(1ll*F[u]*G[v]%Mod+1ll*F[u]*F[v]%Mod)%Mod;
	}
	return;
    }
}
namespace Mayuri{
    int main(){
	for (int i=1;i<=n;i++) F[i]=1ll*n*n%Mod*Y%Mod*Inv((1-Y+Mod)%Mod)%Mod*QPow(i,i)%Mod*Ifc[i]%Mod;
	int N=1;while (N<=n) N<<=1;
	PolyExp(F,G,N);
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;
	int Ans=1ll*G[n]*QPow((1-Y+Mod)%Mod,n)%Mod*Inv(QPow(n,4))%Mod*Fc[n]%Mod;
	printf("%d\n",Ans);return 0;
    }
    void NTT(int *P,int N,int opt){
	int _N=1,l=-1;while (_N<N) _N<<=1,++l;
	for (int i=0;i<N;i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
	for (int i=0;i<N;i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
	for (int i=1;i<N;i<<=1){
	    int dw=QPow(g,(Mod-1)/(i<<1));
	    if (opt==-1) dw=Inv(dw);
	    for (int j=0;j<N;j+=(i<<1))
		for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
		    int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
		    P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
		}
	}
	if (opt==-1){
	    int inv=Inv(N);for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
    }
    void PolyInv(int *A,int *B,int len){
	if (len==1){
	    B[0]=Inv(A[0]);return;
	}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<1;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	
	for (int i=0;i<len;i++) B[i]=((B[i]+B[i])%Mod-I1[i]+Mod)%Mod;
	for (int i=0;i<len<<1;i++) I1[i]=I2[i]=0;
	return;
    }
    void PolyDery(int *A,int *B,int len){
	for (int i=0;i+1<len;i++) B[i]=1ll*A[i+1]*(i+1)%Mod;B[len-1]=0;
	return;
    }
    void PolyInte(int *A,int *B,int len){
	for (int i=1;i<len;i++) B[i]=1ll*A[i-1]*Inv(i)%Mod;
	B[0]=0;return;
    }
    void PolyLn(int *A,int *B,int len){
	PolyDery(A,L1,len);PolyInv(A,L2,len);
	NTT(L1,len<<1,1);NTT(L2,len<<1,1);
	for (int i=0;i<len<<1;i++) L1[i]=1ll*L1[i]*L2[i]%Mod;
	NTT(L1,len<<1,-1);
	PolyInte(L1,B,len);
	for (int i=0;i<len<<1;i++) L1[i]=L2[i]=0;
	return;
    }
    void PolyExp(int *A,int *B,int len){
	if (len==1){
	    B[0]=1;return;
	}
	PolyExp(A,B,len>>1);PolyLn(B,E1,len);
	for (int i=0;i<len;i++) E1[i]=(A[i]-E1[i]+Mod)%Mod,E2[i]=B[i];
	E1[0]=(E1[0]+1)%Mod;
	NTT(E1,len<<1,1);NTT(E2,len<<1,1);
	for (int i=0;i<len<<1;i++) E1[i]=1ll*E1[i]*E2[i]%Mod;
	NTT(E1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=E1[i];
	for (int i=0;i<len<<1;i++) E1[i]=E2[i]=0;
	return;
    }
}
