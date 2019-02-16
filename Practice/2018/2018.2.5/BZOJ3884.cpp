#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll GetPhi(ll x);
ll Pow(ll cnt,ll Mod);
ll Calc(ll p);

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		int x;scanf("%d",&x);
		printf("%lld\n",Calc(x));
	}
}

ll GetPhi(ll x)
{
	ll ret=x;
	for (ll i=2;i*i<=x;i++)
		if (x%i==0)
		{
			ret=ret/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x!=1) ret=ret/x*(x-1);
	return ret;
}

ll Pow(ll cnt,ll Mod)
{
	ll x=2,ret=1;
	while (cnt)
	{
		if (cnt&1) ret=ret*x%Mod;
		x=x*x%Mod;
		cnt=cnt>>1;
	}
	return ret;
}

ll Calc(ll p)
{
	if (p==1) return 0;
	ll nowphi=GetPhi(p);
	return Pow(Calc(nowphi)+nowphi,p);
}
