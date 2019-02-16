#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long

ll Mul(ll a,ll b,ll Mod);
ll QPow(ll x,ll cnt,ll Mod);
pair<ll,ll> PR(ll x);
void Exgcd(ll a,ll b,ll &x,ll &y);

int main(){
	srand(20020729);
	ll e,N,c;scanf("%lld%lld%lld",&e,&N,&c);
	pair<ll,ll> P=PR(N);
	ll r=(P.first-1)*(P.second-1);
	//cout<<P.first<<" "<<P.second<<" "<<r<<endl;
	ll x,y;
	Exgcd(e,r,x,y);
	//cout<<x<<endl;
	x=(x%r+r)%r;
	printf("%lld %lld\n",x,QPow(c,x,N));return 0;
}

ll Mul(ll a,ll b,ll Mod){
	ll r=(long double)a/Mod*b+1e-8;
	ll d=a*b-r*Mod;
	return (d<0)?(d+Mod):d;
}

ll QPow(ll x,ll cnt,ll Mod){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=Mul(ret,x,Mod);
		x=Mul(x,x,Mod);cnt>>=1;
	}
	return ret;
}

pair<ll,ll> PR(ll x){
	do{
		ll k=rand()%x,a=k,b=(Mul(a,a,x)+k)%x,g;
		if (a&&(x%a==0)) return make_pair(a,x/a);
		if (b&&(x%b==0)) return make_pair(b,x/b);
		do{
			g=__gcd(abs(a-b),x);
			if (g!=1) return make_pair(g,x/g);
			a=(Mul(a,a,x)+k)%x;
			b=(Mul(b,b,x)+k)%x;
			b=(Mul(b,b,x)+k)%x;
		}
		while (a!=b);
	}
	while (1);
}

void Exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){
		x=1;y=0;return;
	}
	Exgcd(b,a%b,x,y);
	ll t=x;x=y;y=(t-(ll)(a/b)*y);
	return;
}
