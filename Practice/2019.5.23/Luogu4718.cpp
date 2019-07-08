#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll Ans=0;

ll random(ll l,ll r);
ll Mul(ll a,ll b,ll M);
ll QPow(ll x,ll cnt,ll M);
ll Gcd(ll a,ll b);
bool Miller_Rabin(ll X);
ll Pollard_Rho(ll X);
void Max(ll key);
int main()
{
	srand(20020622);
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		ll key;
		scanf("%lld",&key);
		if (Miller_Rabin(key)) puts("Prime");
		else {
			Ans=0;
			Max(key);
			printf("%lld\n",Ans);
		}
	}
	return 0;
}
ll random(ll l,ll r)
{
	long double d=(long double)rand()/RAND_MAX;
	return min(r,(ll)(d*(r-l+1)+l));
}
ll Mul(ll a,ll b,ll M)
{
	ll p=(a*b-(ll)((long double)a*b/M)*M)%M;
	p=(p%M+M)%M;
	return p;
}
ll QPow(ll x,ll cnt,ll M)
{
	ll ret=1;
	while (cnt) {
		if (cnt&1) ret=Mul(ret,x,M);
		x=Mul(x,x,M);
		cnt>>=1;
	}
	return ret;
}
ll Gcd(ll a,ll b)
{
	return __gcd(a,b);
	if (!a||!b) return a|b;
	int t=__builtin_ctzll(a|b);
	ll tmp;
	a>>=__builtin_ctzll(a);
	while (b) {
		b>>=__builtin_ctzll(b);
		if (a>b) tmp=a,a=b,b=tmp;
		b-=a;
	}
	return a<<t;
}
bool Miller_Rabin(ll X)
{
	if (X<=2) return X==2;
	static int P[]= {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
	for (int i=0; i<16; i++) {
		if (X<=P[i]) continue;
		if (QPow(P[i],X-1,X)!=1) return 0;
		ll DX=X-1;
		while (~DX&1) {
			DX>>=1;
			ll t=QPow(P[i],DX,X);
			if (Mul(t,t,X)==1&&t!=1&&t!=X-1) return 0;
		}
	}
	return 1;
}
ll Pollard_Rho(ll X)
{
	ll a=random(1,X-1),g=1,B=2,x=0,y=0;
	while (1) {
		ll mul=1;
		y=x;
		for (int i=0; i<B; i++) {
			y=(Mul(y,y,X)+a)%X;
			mul=Mul(mul,abs(y-x),X);
			assert(mul<X);
			if (!(i&127)) {
				g=Gcd(X,mul);
				if (g>1) return g;
			}
		}
		x=y;
		B<<=1;
		if (g>1||(g=Gcd(mul,X))>1) break;
	}
	if (g==X) g=1;
	return g;
}
void Max(ll key)
{
	if (Ans>=key) return;
	if (Miller_Rabin(key)) {
		Ans=key;
		return;
	}
	ll g=Pollard_Rho(key);
	while (g==1||g==key) g=Pollard_Rho(key);
	Max(key/g);
	Max(g);
	return;
}
