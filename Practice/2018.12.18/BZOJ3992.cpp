#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20010<<1;
const int Mod=1004535809;
const int inf=2147483647;

int n,m,X,Gmod,phim;
int S[maxN],Map[maxN];
int F1[maxN],F2[maxN],Rader[maxN],I[maxN];

int GetG(int x);
int QPow(int x,int cnt,int M);
void Mul(int *A,int *B);
void NTT(int *P,int len,int opt);

int main(){
	int szs;scanf("%d%d%d%d",&n,&m,&X,&szs);phim=m-1;
	Gmod=GetG(Mod);int g0=GetG(m);//cout<<"g0:"<<g0<<endl;
	for (int i=0,mul=1;i<phim;i++,mul=1ll*mul*g0%m) Map[mul]=i;
	for (int i=1;i<=szs;i++){
		int x;scanf("%d",&x);
		if (x!=0) F1[Map[x]]=F2[Map[x]]=1;
	}
	n--;
	while (n){
		if (n&1) Mul(F1,F2);
		Mul(F2,F2);n>>=1;
	}
	mem(F2,0);F2[Map[1]]=1;Mul(F1,F2);
	printf("%d\n",F1[Map[X]]);return 0;
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
	int pcnt=0,P[100],k=x-1;
	for (int i=2;1ll*i*i<=k;i++)
		if (k%i==0){
			P[++pcnt]=i;while (k%i==0) k/=i;
		}
	if (k!=1) P[++pcnt]=k;
	for (int i=2;i;i++){
		bool flag=1;
		for (int j=1;(j<=pcnt)&&(flag);j++) if (QPow(i,(x-1)/P[j],x)==1) flag=0;
		if (flag) return i;
	}
}

void Mul(int *A,int *B){
	//cout<<"Mul:"<<endl;
	//for (int i=0;i<phim;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<phim;i++) cout<<B[i]<<" ";cout<<endl;
	int N;for (N=1;N<phim+phim;N<<=1);
	for (int i=0;i<N;i++) I[i]=B[i];
	NTT(A,N,1);NTT(I,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*I[i]%Mod;
	NTT(A,N,-1);
	//for (int i=0;i<phim+phim;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=0;i<phim;i++) A[i]=(A[i]+A[i+phim])%Mod;
	for (int i=phim;i<N;i++) A[i]=0;
	return;
}

void NTT(int *P,int len,int opt){
	int L=0,N;for (N=1;N<len;N<<=1) L++;
	for (int i=0;i<len;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	//cout<<len<<" - "<<L<<endl;for (int i=0;i<len;i++) cout<<i<<" "<<Rader[i]<<endl;cout<<endl;
	for (int i=0;i<len;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<len;i<<=1){
		int dw=QPow(Gmod,(Mod-1)/(i<<1),Mod);
		if (opt==-1) dw=QPow(dw,Mod-2,Mod);
		for (int j=0;j<len;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2,Mod);
		for (int i=0;i<len;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
