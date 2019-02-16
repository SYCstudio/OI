#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100*4;
const int Mod=998244353;
const int g=3;
const int inf=2147483647;

int n,base,p,x,N;
int Rader[maxN],F[maxN],G[maxN],H[maxN];

void Solve(int len);
void Plus(int &x,int y,int mod);
int QPow(int x,int cnt,int mod);
void Mul(int *A,int *B,int len);
void NTT(int *P,int len,int opt);

int main(){
	scanf("%d%d%d%d",&n,&base,&p,&x);
	//for (int i='a';i<='z';i++) cout<<i%p<<" ";cout<<endl;
	for (N=1;N<p+p;N<<=1);
	Solve(n);
	printf("%d\n",G[x]);return 0;
}

void Solve(int len){
	if (len==0){
		F[0]=1;return;
	}
	if (len&1){
		Solve(len-1);
		for (int i=0;i<p;i++) H[i]=0;
		for (int i=0;i<p;i++)
			for (int j='a';j<='z';j++)
				Plus(H[(1ll*i*base%p+j)%p],F[i],Mod);
		for (int i=0;i<p;i++) F[i]=H[i],Plus(G[i],F[i],Mod);
	}
	else{
		Solve(len>>1);
		int b=QPow(base,len>>1,p);
		for (int i=0;i<N;i++) H[i]=0;
		for (int i=0;i<p;i++) Plus(H[1ll*i*b%p],G[i],Mod);
		Mul(H,F,N);
		for (int i=0;i<N;i++) Plus(G[i%p],H[i],Mod);
		for (int i=0;i<N;i++) H[i]=0;
		for (int i=0;i<p;i++) Plus(H[1ll*i*b%p],F[i],Mod);
		Mul(H,F,N);
		for (int i=0;i<p;i++) F[i]=0;
		for (int i=0;i<N;i++) Plus(F[i%p],H[i],Mod);
		
	}
	//cout<<len<<":"<<endl;
	//for (int i=0;i<p;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=0;i<p;i++) cout<<G[i]<<" ";cout<<endl;
	return;
}

int QPow(int x,int cnt,int mod){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;cnt>>=1;
	}
	return ret;
}

void Plus(int &x,int y,int mod){
	x=(x+y)%mod;return;
}

void Mul(int *A,int *B,int len){
	//cout<<"Mul:"<<endl;
	//for (int i=0;i<len;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<len;i++) cout<<B[i]<<" ";cout<<endl;
	NTT(A,len,1);NTT(B,len,1);
	for (int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);NTT(B,len,-1);

	//for (int i=0;i<len;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<len;i++) cout<<B[i]<<" ";cout<<endl;
	
	return;
}

void NTT(int *P,int len,int opt){
	int nn,L=0;
	for (nn=1;nn<len;nn<<=1) L++;
	for (int i=0;i<len;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<len;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<len;i<<=1){
		int dw=QPow(g,(Mod-1)/(i<<1),Mod);
		if (opt==-1) dw=QPow(dw,Mod-2,Mod);
		for (int j=0;j<len;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(len,Mod-2,Mod);
		for (int i=0;i<len;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
