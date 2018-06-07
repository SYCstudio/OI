#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=10000010;
const int inf=2147483647;
const ll Mod=20101009;

int Mu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];
ll Sum[maxNum];

void GetMu();
ll Calc(ll n,ll m);

int main()
{
	GetMu();
	ll n,m;scanf("%lld%lld",&n,&m);if (n>m) swap(n,m);
	ll ans=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ll s=(last+i)*(last-i+1)/2;
		ans=(ans+s%Mod*Calc(n/i,m/i)%Mod)%Mod;
	}
	printf("%lld\n",ans);
	return 0;
}

void GetMu()
{
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	for (int i=1;i<maxNum;i++) Sum[i]=((Sum[i-1]+(ll)Mu[i]*(ll)i*(ll)i)%Mod+Mod)%Mod;
	return;
}

ll Calc(ll n,ll m)
{
	if (n>m) swap(n,m);
	ll ret=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ll l1=n/i,l2=m/i;
		ll s1=(1+l1)*l1/2%Mod,s2=(1+l2)*l2/2%Mod;
		ret=(ret+((Sum[last]-Sum[i-1])+Mod)%Mod*s1%Mod*s2%Mod)%Mod;
	}
	return (ret%Mod+Mod)%Mod;
}
