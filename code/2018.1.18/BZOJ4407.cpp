#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=5000010;
const ll Mod=1e9+7;
const int inf=2147483647;

int pricnt=0,Prime[maxNum];
bool notprime[maxNum];
ll H[maxNum];
ll Pow[maxNum];

int K;

void Init();
int QPow(ll x,int cnt);

int main()
{
	int T;
	scanf("%d%d",&T,&K);
	Init();
	while (T--)
	{
		ll n,m;scanf("%lld%lld",&n,&m);if (n>m) swap(n,m);
		ll ans=0;
		for (ll i=1,last;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans=(ans+(H[last]-H[i-1]+Mod)%Mod*(ll)((n/i))%Mod*(ll)((m/i))%Mod)%Mod;
		}
		printf("%lld\n",ans%Mod);
	}
	return 0;
}

void Init()
{
	notprime[1]=1;H[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Pow[pricnt]=QPow(i,K),H[i]=Pow[pricnt]-1;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				H[i*Prime[j]]=H[i]*Pow[j]%Mod;
				break;
			}
			H[i*Prime[j]]=H[i]*H[Prime[j]]%Mod;
		}
	}
	for (int i=1;i<maxNum;i++) H[i]=(H[i]+H[i-1])%Mod;
	return;
}

int QPow(ll x,int cnt)
{
	ll ret=1;
	while (cnt)
	{
		if (cnt&1) ret=ret*x%Mod;
		x=x*x%Mod;
		cnt=cnt>>1;
	}
	return ret;
}
