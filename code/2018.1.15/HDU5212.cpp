#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=10010;
const int Mod=10007;
const int inf=2147483647;

int Mu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];
int n,Cnt[maxNum];
ll G[maxNum];

void GetMu();

int main()
{
    GetMu();
    for (int i=1;i<maxNum;i++)//Get G(i)
    {
		int j;
		for (j=1;j*j<i;j++)
			if (i%j==0)
				G[i]=((G[i]+Mu[i/j]*j%Mod*(j-1)%Mod+Mu[i/(i/j)]*(i/j)%Mod*(i/j-1)%Mod)%Mod+Mod)%Mod;
		if (j*j==i) G[i]=((G[i]+Mu[i/j]*j%Mod*(j-1)%Mod)%Mod+Mod)%Mod;
    }
    while (scanf("%d",&n)!=EOF)
    {
		mem(Cnt,0);
		for (int i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			Cnt[x]++;
		}
		ll ans=0;
		for (int i=1;i<maxNum;i++)
		{
			ll sum=0;
			for (int j=i;j<maxNum;j=j+i) sum=(sum+Cnt[j])%Mod;
			sum=sum*sum%Mod;
			ans=((ans+sum*G[i]%Mod)%Mod+Mod)%Mod;
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
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j])<maxNum;j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
    }
    return;
}
