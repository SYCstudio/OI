#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

int main()
{
	ll n,K;scanf("%lld%lld",&n,&K);
	ll ans=0;
	ans=n*K;
	for (ll i=1,last;i<=n;i=last+1)
	{
		if ((ll)(K/i)==0) break;
		last=min(K/((ll)(K/i)),n);
		ll s1=(last+i)*(last-i+1)/2;
		//cout<<s1<<" "<<ans<<endl;
		ans=ans-s1*(ll)((K/i));
	}
	printf("%lld\n",ans);
	return 0;
}
