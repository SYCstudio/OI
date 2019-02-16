#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;

#define ll long long

const int maxN=10100000;
const int Mod=1000000007;
const int inf=2147483647;

bool notprime[maxN];
int pcnt,P[maxN],Mu[maxN];
map<int,int> Mp;

void Init();
int GetMu(ll n);
int Calc(ll n);

int main(){
	Init();ll n;scanf("%lld",&n);
	int Ans=0;
	for (ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		//cout<<"("<<i<<","<<j<<")"<<endl;
		int m=(GetMu(j)-GetMu(i-1)+Mod)%Mod,k=Calc(n/i);
		k=1ll*k*k%Mod;m=(1ll*m*k%Mod)%Mod;
		Ans=(Ans+m)%Mod;
	}
	printf("%d\n",Ans);return 0;
}

void Init(){
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i,Mu[i]=Mod-1;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;
			if (i%P[j]==0) break;
			Mu[i*P[j]]=Mod-Mu[i];
		}
	}
	for (int i=2;i<maxN;i++) Mu[i]=(Mu[i]+Mu[i-1])%Mod;
	return;
}

int GetMu(ll n){
	//cout<<"GetMu:"<<n<<" "<<endl;
	if (n<maxN) return Mu[n];
	if (Mp.count(n)) return Mp[n];
	int ret=0;
	for (ll i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ret=(ret+1ll*(j-i+1)*GetMu(n/i)%Mod)%Mod;
	}
	return Mp[n]=(1-ret+Mod)%Mod;
}

int Calc(ll n){
	int ret=0;
	for (ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		ret=(ret+1ll*(j-i+1)*(n/i)%Mod)%Mod;
	}
	return ret;
}
