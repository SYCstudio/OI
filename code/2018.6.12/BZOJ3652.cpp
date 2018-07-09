#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=70;
const int inf=2147483647;

ll n;
ld p;
ll Num[maxN],bit,Bin[maxN];

ld Do1();
ld Do2();

int main()
{
	scanf("%lld%LF",&n,&p);n--;
	ll tmp=n;
	while (tmp) Num[bit++]=tmp&1,tmp>>=1;
	bit--;
	Bin[0]=1;for (int i=1;i<=bit+2;i++) Bin[i]=Bin[i-1]<<1;
	
	ld Ans=Do1()*p/(n+1)+Do2()*(1.0-p)/(n+1)/(n+1);
	printf("%.6LF\n",Ans);
	return 0;
}

ld Do1()//未加密
{
	ld Ret=(ld)1.0*(ld)(n+1)*(ld)(Bin[bit+1]-1);
	ll cnt=Bin[bit+1];
	for (int i=bit;i>=0;i--)
		if (Num[i]) cnt>>=1;
		else Ret-=(ld)(cnt>>1)*(ld)(Bin[i]);
	return Ret;
}

ld Do2()//加密
{
	ld Ret=0;
	ll up=0;
	for (int i=bit;i>=0;i--)
	{
		ld p1=(ld)up*(ld)Bin[i];
		if (Num[i]) p1=p1+(ld)(n&(Bin[i]-1))+1;
		ld p2=(ld)(n-p1+1);
		Ret=Ret+(ld)p1*p2*2.0*(ld)Bin[i];
		up=(up<<1)+Num[i];
	}
	return Ret;
}
