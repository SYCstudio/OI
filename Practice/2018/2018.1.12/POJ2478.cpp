#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=1000010;
const int inf=2147483647;

ll phi[maxNum];
ll sum[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void Phi();

int main()
{
    Phi();
    //for (int i=1;i<=20;i++) cout<<phi[i]<<" ";cout<<endl;
    sum[1]=0;
    for (int i=2;i<maxNum;i++) sum[i]=sum[i-1]+phi[i];
    int n;
    while (scanf("%d",&n)!=EOF)
    {
		if (n==0) break;
		printf("%lld\n",sum[n]);
    }
    return 0;
}

void Phi()
{
    notprime[1]=1;phi[1]=1;
    for (int i=2;i<maxNum;i++)
    {
		if (notprime[i]==0) Prime[++pricnt]=i,phi[i]=i-1;
		for (int j=1;(j<=pricnt)&&((ll)i*Prime[j])<maxNum;j++)
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
