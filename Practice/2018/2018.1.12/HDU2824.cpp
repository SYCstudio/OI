#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=3000010;
const int inf=2147483647;

int phi[maxNum];
//ll sum[maxNum];空间开不下呜呼
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetPhi();

int main()
{
    GetPhi();
    //for (int i=1;i<maxNum;i++) sum[i]=sum[i-1]+phi[i];
    int l,r;
    while (scanf("%d%d",&l,&r)!=EOF)
    {
		ll ans=0;
		for (int i=l;i<=r;i++) ans=ans+(ll)phi[i];
		printf("%lld\n",ans);
    }
    return 0;
}

void GetPhi()
{
    notprime[1]=1;phi[1]=0;
    for (int i=2;i<maxNum;i++)
    {
		if (notprime[i]==0) phi[i]=i-1,Prime[++pricnt]=i;
		for (int j=1;(j<=pricnt)&&((ll)Prime[j]*i<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				phi[i*Prime[j]]=phi[i]*Prime[j];
				break;
			}
			phi[i*Prime[j]]=phi[i]*phi[Prime[j]];
		}
    }
    return;
}
