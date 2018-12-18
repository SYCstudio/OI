#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000<<2;
const char AGCT[]="AGCT";
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m,K;
int N,L,Rader[maxN],Mark[maxN];
char S[maxN],T[maxN];
int A[maxN],B[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int opt);

int main(){
	scanf("%d%d%d",&n,&m,&K);scanf("%s",S);scanf("%s",T);reverse(&T[0],&T[m]);
	for (N=1;N<n+n;N<<=1) L++;for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int c=0;c<4;c++){
		for (int i=0,lst=-K-K-10;i<n;i++){
			if (S[i]==AGCT[c]) lst=i;
			if (i-lst<=K) A[i]=1;
		}
		for (int i=n-1,lst=n+K+K+10;i>=0;i--){
			if (S[i]==AGCT[c]) lst=i;
			if (lst-i<=K) A[i]=1;
		}
		int sum=0;
		for (int i=0;i<m;i++) B[i]=(T[i]==AGCT[c]),sum+=B[i];
		//cout<<AGCT[c]<<endl;
		//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
		//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
		//cout<<sum<<endl;
		NTT(A,1);NTT(B,1);
		for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
		NTT(A,-1);
		for (int i=m-1;i<n;i++) if (sum!=A[i]) Mark[i]=1;
		for (int i=0;i<N;i++) A[i]=B[i]=0;
	}
	int Ans=0;for (int i=m-1;i<n;i++) Ans+=(Mark[i]==0);
	printf("%d\n",Ans);return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int opt){
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
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
