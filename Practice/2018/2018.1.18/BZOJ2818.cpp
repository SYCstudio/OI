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

int Mu[maxNum],Musum[maxNum];
int Prisum[maxNum];
int pricnt=0,Prime[maxNum/1000];
bool notprime[maxNum];

void Init();
ll Calc(int n);

int main()
{
	Init();
	int n;scanf("%d",&n);
	ll ans=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=n/(n/i);
		ans=ans+(Prisum[last]-Prisum[i-1])*Calc(n/i);
	}
	printf("%lld\n",ans);
	return 0;
}

void Init()
{
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1,Prisum[i]=1;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	//for (int i=1;i<=10;i++) cout<<Prisum[i]<<" ";cout<<endl;
	for (int i=1;i<maxNum;i++) Musum[i]=Musum[i-1]+Mu[i],Prisum[i]+=Prisum[i-1];
	return;
}

ll Calc(int n)
{
	ll ret=0;
	for (ll i=1,last;i<=n;i=last+1)
	{
		last=n/(n/i);
		ret=ret+(Musum[last]-Musum[i-1])*(ll)((n/i))*(ll)((n/i));
	}
	//cout<<n<<" "<<ret<<endl;
	return ret;
}
