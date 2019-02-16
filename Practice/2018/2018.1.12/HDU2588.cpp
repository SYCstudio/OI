#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll Phi(ll x);

int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
		ll n,m;scanf("%lld%lld",&n,&m);
		ll ans=0;
		for (ll i=1;i*i<=n;i++)
			if (n%i==0)
			{
				if (i>=m) ans=ans+Phi(n/i);
				if ((n/i>=m)&&(i*i!=n)) ans=ans+Phi(i);
			}
		printf("%lld\n",ans);
    }
    return 0;
}

ll Phi(ll x)//求φ
{
    ll ret=x;
    for (ll i=2;i*i<=x;i++)
		if (x%i==0)
		{
			ret=ret/i*(i-1);
			while (x%i==0) x=x/i;
		}
    if (x>1) ret=ret/x*(x-1);
    return ret;
}
