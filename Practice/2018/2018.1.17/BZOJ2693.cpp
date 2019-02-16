#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=10000100;
const ll Mod=100000009;
const int inf=2147483647;

ll Sum[maxNum];
ll pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void Sieve();

int main()
{
	Sieve();
	int T;scanf("%d",&T);
	while (T--)
	{
		ll n,m;scanf("%lld%lld",&n,&m);if (n>m) swap(n,m);
		ll ans=0;
		for (ll i=1,last;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ll l1=n/i,l2=m/i;
			ll s1=l1*(1ll+l1)/2%Mod,s2=l2*(1ll+l2)/2%Mod;
			ans=((ans+(((Sum[last]-Sum[i-1])%Mod+Mod)%Mod)*s1%Mod*s2%Mod)%Mod+Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

void Sieve()
{
	notprime[1]=1;Sum[1]=1;
	for (ll i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Sum[i]=(i-i*i+Mod)%Mod;
		for (ll j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				Sum[i*Prime[j]]=Sum[i]*Prime[j]%Mod;break;
			}
			Sum[i*Prime[j]]=Sum[i]*Sum[Prime[j]]%Mod;
		}
	}
	for (int i=1;i<maxNum;i++) Sum[i]=((Sum[i]+Sum[i-1])%Mod+Mod)%Mod;
	return;
}
