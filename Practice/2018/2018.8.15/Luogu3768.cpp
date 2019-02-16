#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100000;
const int inf=2147483647;

ll N,Mod;
ll inv2,inv6;
bool notprime[maxN];
ll pcnt,Prime[maxN],Phi[maxN];
map<ll,ll> Rc;

ll QPow(ll x,ll cnt);
void Init();
ll CalcSum(ll n);
ll CalcSum2(ll n);
ll Calc(ll n);

int main()
{
	scanf("%lld%lld",&Mod,&N);
	inv2=QPow(2,Mod-2);inv6=QPow(6,Mod-2);
	Init();

	ll Ans=0;
	for (ll i=1,j;i<=N;i=j+1){
		j=N/(ll)(N/i);
		Ans=(Ans+1ll*CalcSum(N/i)%Mod*CalcSum(N/i)%Mod*(Calc(j)-Calc(i-1)+Mod)%Mod)%Mod;
	}

	printf("%lld\n",Ans);

	return 0;
}

ll QPow(ll x,ll cnt){
	ll ret=1;x%=Mod;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Init(){
	notprime[1]=1;Phi[1]=1;
	for (ll i=2;i<maxN;i++){
		if (notprime[i]==0) Prime[++pcnt]=i,Phi[i]=i-1;
		for (ll j=1;(j<=pcnt)&&(1ll*i*Prime[j]<maxN);j++){
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0){
				Phi[i*Prime[j]]=Phi[i]*Prime[j];
				break;
			}
			Phi[i*Prime[j]]=Phi[i]*Phi[Prime[j]];
		}
	}

	//for (int i=1;i<=40;i++) cout<<Phi[i]<<" ";cout<<endl;

	for (int i=1;i<maxN;i++) Phi[i]=1ll*Phi[i]*i%Mod*i%Mod;
	for (int i=1;i<maxN;i++) Phi[i]=(Phi[i]+Phi[i-1])%Mod;
	return;
}

ll CalcSum(ll n){
	n%=Mod;
	return 1ll*n%Mod*(n+1)%Mod*inv2%Mod;
}

ll CalcSum2(ll n){
	n%=Mod;
	return 1ll*n%Mod*(n+1)%Mod*(n+n+1)%Mod*inv6%Mod;
}

ll Calc(ll n){
	if (n<maxN) return Phi[n];
	if (Rc.count(n)) return Rc[n];
	ll ret=0;
	for (ll i=2,j;i<=n;i=j+1){
		j=n/(ll)(n/i);
		ret=(ret+1ll*(CalcSum2(j)-CalcSum2(i-1)+Mod)%Mod*Calc(n/i)%Mod)%Mod;
	}
	ret=(1ll*CalcSum(n)%Mod*CalcSum(n)%Mod-ret+Mod)%Mod;
	return Rc[n]=ret;
}
