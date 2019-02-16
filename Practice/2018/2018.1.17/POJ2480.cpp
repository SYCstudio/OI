#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll Phi(ll x);

int main()
{
	ll n;
	while (scanf("%lld",&n)!=EOF)
	{
		ll ans=0;
		for (ll i=1;(ll)i*(ll)i<=n;i++)
			if (n%i==0)
			{
				ans=ans+(ll)i*(ll)Phi(n/i);
				if (i*i!=n) ans=ans+(ll)(n/i)*(ll)Phi(i);
			}
		printf("%lld\n",ans);
	}
	return 0;
}

ll Phi(ll x)
{
	//cout<<"Phi:"<<x<<" ";
	ll ret=x;
	for (ll i=2;(ll)i*(ll)i<=x;i++)
		if (x%i==0)
		{
			ret=ret/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x!=1) ret=ret/x*(x-1);
	//cout<<ret<<endl;
	return ret;
}
