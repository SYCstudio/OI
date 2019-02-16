#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=100010;
const int inf=2147483647;

int a,b,c,d,k;
ll Mu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();

int main()
{
    GetMu();
    int T;scanf("%d",&T);
    for (int ti=1;ti<=T;ti++)
    {
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if (k==0)
		{
			printf("Case %d: 0\n",ti);
			continue;
		}
		if (d<b) swap(b,d);
		ll ans=0,sum=0;
		for (ll i=k;i<=b;i+=k)
			if (i%k==0) ans=ans+Mu[i/k]*(ll)(b/i)*(ll)(d/i);
		for (ll i=k;i<=b;i+=k)
			if (i%k==0) sum=sum+Mu[i/k]*(ll)(b/i)*(ll)(b/i);
		printf("Case %d: %lld\n",ti,ans-sum/2);
    }
    return 0;
}

void GetMu()
{
    Mu[1]=1;notprime[1]=1;
    for (int i=2;i<maxNum;i++)
    {
		if (notprime[i]==0) Mu[i]=-1,Prime[++pricnt]=i;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
    }
    return;
}
