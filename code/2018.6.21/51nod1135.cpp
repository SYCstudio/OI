#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int n;
ll pcnt,P[100000];

ll QPow(ll x,ll cnt,ll mod);

int main()
{
	scanf("%d",&n);
	int num=n-1;
	for (int i=2;i<=sqrt(num);i++)
		if (num%i==0)
		{
			P[++pcnt]=i;
			while (num%i==0) num/=i;
		}

	for (int g=2;g<=n-1;g++)
	{
		bool flag=1;
		for (int i=1;i<=pcnt;i++)
			if (QPow(g,(n-1)/P[i],n)==1){
				flag=0;break;
			}
		if (flag){
			printf("%d\n",g);break;
		}
	}
}

ll QPow(ll x,ll cnt,ll mod)
{
	ll Ret=1;
	while (cnt){
		if (cnt&1) Ret=Ret*x%mod;
		x=x*x%mod;cnt>>=1;
	}
	return Ret;
}
