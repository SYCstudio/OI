#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int Mod=998244353;
const int G=3;

ll QPow(ll x,ll cnt);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		ll n,s,a[4];
		scanf("%lld%lld%lld%lld%lld%lld",&n,&s,&a[0],&a[1],&a[2],&a[3]);
		int w=QPow(G,(Mod-1)/4),inv4=QPow(4,Mod-2),Ans=0;
		for (int d=0; d<4; d++) {
			int sum=0;
			for (int j=0; j<4; j++) sum=(sum+1ll*QPow((1ll*QPow(w,j)*s%Mod+1),n)*QPow(w,4-j*d%4)%Mod)%Mod;
			sum=1ll*sum*inv4%Mod*a[d]%Mod;
			Ans=(Ans+sum)%Mod;
		}
		printf("%d\n",Ans);
	}
	return 0;
}
ll QPow(ll x,ll cnt)
{
	x=x%Mod;
	cnt=cnt%(Mod-1);
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}