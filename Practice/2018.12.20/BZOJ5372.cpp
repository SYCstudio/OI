#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=505000*4;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,N,L;
char Input[maxN];
int A1[maxN],B1[maxN],A2[maxN],B2[maxN];
int Rader[maxN];
bool Mark[maxN];

int QPow(int x,int cnt);
void Mul(int *A,int *B);
void NTT(int *P,int opt);

int main(){
	scanf("%s",Input);n=strlen(Input);
	for (int i=0;i<n;i++)
		if (Input[i]=='0') A1[i]=1,B2[n-i-1]=1;
		else if (Input[i]=='1') B1[n-i-1]=1,A2[i]=1;
	N=1;L=0;while (N<n+n) ++L,N<<=1;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));

	//for (int i=0;i<N;i++) cout<<A1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<A2[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B2[i]<<" ";cout<<endl<<endl;
	
	Mul(A1,B1);Mul(A2,B2);

	//for (int i=0;i<N;i++) cout<<A1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<A2[i]<<" ";cout<<endl;

	for (int i=0;i<n-i-1;i++) swap(A1[i],A1[n-i-1]),swap(A2[i],A2[n-i-1]);

	//for (int i=0;i<N;i++) cout<<A1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<A2[i]<<" ";cout<<endl;
	
	ll Ans=1ll*n*n;
	for (int i=1;i<n;i++){
		bool flag=1;
		for (int j=n-i;j<=n;j=j+n-i) if ((A1[j])||(A2[j])) {flag=0;break;}
		//cout<<i<<" "<<flag<<endl;
		if (flag) Ans^=1ll*i*i;
	}
	printf("%lld\n",Ans);return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Mul(int *A,int *B){
	NTT(A,1);NTT(B,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,-1);return;
}

void NTT(int *P,int opt){
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

