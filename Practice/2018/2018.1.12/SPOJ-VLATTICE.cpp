#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=1000010;
const int inf=2147483647;

int Mu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();

int main()
{
    GetMu();
    int T;scanf("%d",&T);
    while (T--)
    {
	int n;scanf("%d",&n);
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
	    ll x=n/i;
	    ans=ans+(ll)Mu[i]*(ll)x*(ll)x*(ll)(x+3);
	}
	printf("%lld\n",ans+3ll);
    }
    return 0;
}

void GetMu()
{
    Mu[1]=1;notprime[1]=1;
    for (int i=2;i<maxNum;i++)
    {
	if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1;
	for (int j=1;(j<=pricnt)&&((ll)Prime[j]*(ll)i<maxNum);j++)
	{
	    notprime[i*Prime[j]]=1;
	    if (i%Prime[j]==0) break;
	    Mu[i*Prime[j]]=-Mu[i];
	}
    }
    return;
}
