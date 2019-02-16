#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=100010;
const int inf=2147483647;

int Mu[maxNum];
ll Musum[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();
ll Calc(ll n,ll m);

int main()
{
	GetMu();
	ll n,m;
	scanf("%lld%lld",&n,&m);if (m<n) swap(n,m);
	ll ans=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ans=ans+(ll)(last+i)*(ll)(last-i+1)/2ll*Calc(n/i,m/i);
	}
	printf("%lld\n",ans*2-n*m);
	return 0;
}

void GetMu()
{
	Mu[1]=1;notprime[1]=1;
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
	for (int i=1;i<maxNum;i++) Musum[i]=Musum[i-1]+Mu[i];
	return;
}

ll Calc(ll n,ll m)
{
	if (n>m) swap(n,m);
	ll ret=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ret=ret+(Musum[last]-Musum[i-1])*(ll)(n/i)*(ll)(m/i);
	}
	return ret;
}
