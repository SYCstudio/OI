#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=1000010;
const int inf=2147483647;

int n;
ll Mu[maxNum],SumMu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];
int L,W,H;

void GetMu();

int main()
{
    GetMu();
    while (scanf("%d%d%d",&L,&W,&H)!=EOF)
    {
		L--;W--;H--;
		ll ans=3;
		int limit=min(L,min(W,H));
		for (int i=1,last=1;i<=limit;i=last+1)
		{
			ll k1=L/i,k2=W/i,k3=H/i;
			last=min(L/k1,min(W/k2,H/k3));
			ans=ans+(SumMu[last]-SumMu[i-1])*k1*k2*k3;
		}
		limit=min(L,W);
		for (int i=1,last=1;i<=limit;i=last+1)
		{
			ll k1=L/i,k2=W/i;
			last=min(L/k1,W/k2);
			ans=ans+(SumMu[last]-SumMu[i-1])*k1*k2;
		}
		limit=min(L,H);
		for (int i=1,last=1;i<=limit;i=last+1)
		{
			ll k1=L/i,k2=H/i;
			last=min(L/k1,H/k2);
			ans=ans+(SumMu[last]-SumMu[i-1])*k1*k2;
		}
		limit=min(W,H);
		for (int i=1,last=1;i<=limit;i=last+1)
		{
			ll k1=W/i,k2=H/i;
			last=min(W/k1,H/k2);
			ans=ans+(SumMu[last]-SumMu[i-1])*k1*k2;
		}
		printf("%lld\n",ans);
    }
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
			if (i%Prime[j]!=0) Mu[i*Prime[j]]=-Mu[i];
			else break;
		}
    }
    for (int i=1;i<maxNum;i++) SumMu[i]=SumMu[i-1]+Mu[i];
    return;
}
