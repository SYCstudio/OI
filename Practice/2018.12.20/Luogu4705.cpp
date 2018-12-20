#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline
#define RG register

const int maxN=101000*8;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m,T;
int Fac[maxN],Ifc[maxN];
int a[maxN],b[maxN],R[maxN];
int I1[maxN],I2[maxN],L1[maxN],L2[maxN],Dv[19][maxN];
int A[maxN],B[maxN];

IL int Input();
IL int Plus(RG int x,RG int y);
IL int Minus(RG int x,RG int y);
IL int QPow(RG int x,RG int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);
void PolyInte(int *A,int *B,int len);
void PolyDery(int *A,int *B,int len);
void PolyLn(int *A,int *B,int len);
void GetPowSum(int *A,int *B,int len,int top);
void Divide(int *A,int d,int l,int r);

int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	Fac[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	n=Input();m=Input();//scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) a[i]=Input();//scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) b[i]=Input();//scanf("%d",&b[i]);
	T=Input();//scanf("%d",&T);
	//cerr<<"Input over"<<endl;
	GetPowSum(a,A,n,T);GetPowSum(b,B,m,T);
	//cerr<<"Divide over"<<endl;
	for (int i=0;i<=T;i++) A[i]=1ll*A[i]*Ifc[i]%Mod,B[i]=1ll*B[i]*Ifc[i]%Mod;
	int N=1;while (N<=T+T) N<<=1;
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=1;i<=T;i++) printf("%lld\n",1ll*A[i]*Fac[i]%Mod*QPow(1ll*n*m%Mod,Mod-2)%Mod);
	return 0;
}

IL int Input(){
	char ch=getchar();int x=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x;
}

IL int Plus(RG int x,RG int y){
	x+=y;if (x>=Mod) x-=Mod;
	return x;
}

IL int Minus(RG int x,RG int y){
	x-=y;if (x<0) x+=Mod;
	return x;
}

IL int QPow(RG int x,RG int cnt){
	RG int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,RG int N,RG int opt){
	RG int L=0,l=1,i,j,k,X,Y,dw,w;while (l<N) ++L,l<<=1;for (i=0;i<N;++i) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	for (i=0;i<N;++i) if (i<R[i]) swap(P[i],P[R[i]]);
	for (i=1;i<N;i<<=1){
		dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (j=0;j<N;j+=(i<<1))
			for (k=0,w=1;k<i;++k,w=1ll*w*dw%Mod){
				X=P[j+k];Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=Plus(X,Y);P[j+k+i]=Minus(X,Y);
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (i=0;i<N;++i) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void PolyInv(int *A,int *B,RG int len){
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	RG int i,l=len<<1;
	for (i=0;i<len;++i) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,l,1);NTT(I2,l,1);
	for (i=0;i<l;++i) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,l,-1);
	for (i=0;i<len;++i) B[i]=Minus(Plus(B[i],B[i]),I1[i]);
	for (i=0;i<l;++i) I1[i]=I2[i]=0;
	return;
}

void PolyInte(int *A,int *B,RG int len){
	for (int i=0;i<len-1;++i) B[i+1]=1ll*A[i]*QPow(i+1,Mod-2)%Mod;
	B[0]=B[len]=0;return;
}

void PolyDery(int *A,int *B,RG int len){
	for (int i=1;i<len;++i) B[i-1]=1ll*i*A[i]%Mod;
	return;
}

void PolyLn(int *A,int *B,RG int len){
	PolyDery(A,L1,len);PolyInv(A,L2,len);
	RG int i,l=len<<1;
	NTT(L1,l,1);NTT(L2,l,1);
	for (int i=0;i<l;i++) L1[i]=1ll*L1[i]*L2[i]%Mod;
	NTT(L1,l,-1);
	for (int i=len;i<l;i++) L1[i]=0;
	PolyInte(L1,B,len);
	for (int i=0;i<l;i++) L1[i]=L2[i]=0;
	return;
}

void GetPowSum(int *A,int *B,int len,int top){
	Divide(A,0,1,len);//cerr<<"Divide over"<<endl;
	int N=1;while (N<=top) N<<=1;
	for (int i=len+1;i<N;i++) Dv[0][i]=0;
	for (int i=top+1;i<max(N,len);++i) Dv[0][i]=0;
	PolyLn(Dv[0],B,N);//cerr<<"Ln over"<<endl;
	mem(Dv,0);
	for (int i=top+1;i<N;++i) B[i]=0;
	B[0]=len;
	for (int i=1;i<=top;++i) B[i]=(1ll*B[i]*i%Mod*((i&1)?(1):(-1))+Mod)%Mod;
	return;
}

void Divide(int *A,RG int d,RG int l,RG int r){
	if (l==r){
		Dv[d][0]=1;Dv[d][1]=A[l];return;
	}
	RG int mid=(l+r)>>1,sz=r-l+1,N=1,i;while (N<=sz) N<<=1;
	Divide(A,d+1,l,mid);
	for (i=0;i<=sz;++i) Dv[d][i]=Dv[d+1][i];
	for (i=0;i<N;++i) Dv[d+1][i]=0;
	Divide(A,d+1,mid+1,r);
	NTT(Dv[d],N,1);NTT(Dv[d+1],N,1);
	for (i=0;i<N;++i) Dv[d][i]=1ll*Dv[d][i]*Dv[d+1][i]%Mod;
	NTT(Dv[d],N,-1);
	for (i=sz+1;i<N;++i) Dv[d][i]=0;
	for (i=0;i<N;++i) Dv[d+1][i]=0;
	return;
}
