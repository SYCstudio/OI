#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll n,r;ld x;

ll Calc(ll a,ll b,ll c,ll n);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%lld%lld",&n,&r);x=sqrt(r);
		if ((ll)x*(ll)x==r) printf("%lld\n",(ll)x&1? ((n&1)?(-1ll):0ll) : (n));
		else printf("%lld\n",n-2ll*Calc(1,0,1,n)+4ll*Calc(1,0,2,n));
	}
	return 0;
}

ll Calc(ll a,ll b,ll c,ll n){
	//cout<<a<<" "<<b<<" "<<c<<endl;
	if (n<=0) return 0;
	//if (n==1) return (ll)(((ld)a*x+(ld)b)/(ld)c);
	ll d=abs(__gcd(a,__gcd(b,c)));a/=d;b/=d;c/=d;
	ll k=(a*x+b)/c;
	if (k>=1) return Calc(a,b-k*c,c,n)+n*(n+1)/2*k;
	else return n*(ll)((a*x+b)/c*n)-Calc(a*c,-b*c,a*a*r-b*b,(a*x+b)/c*n);
}
