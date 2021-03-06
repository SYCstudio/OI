#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
ll A[maxN],P[maxN];

ll Exgcd(ll a,ll b,ll &x,ll &y);
ll Mul(ll x,ll y,ll Mod);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&P[i],&A[i]);

	bool flag=1;
	for (int i=2;i<=n;i++){
		ll x,y;
		ll gcd=Exgcd(P[1],P[i],x,y),dt=A[i]-A[1];
		if (dt%gcd!=0){
			flag=0;break;
		}
		ll t=P[i]/gcd;x=Mul(x,dt/gcd,t);
		x=(x%t+t)%t;
		ll tmp=x;
        tmp=Mul(tmp,P[1],P[1]*t);
		A[1]=(A[1]+Mul(x,P[1],P[1]*t))%(P[1]*t);
		P[1]=P[1]*t;
	}
	printf("%lld\n",(A[1]%P[1]+P[1])%P[1]);

	return 0;
}

ll Exgcd(ll a,ll b,ll &x,ll &y){
	if (a==0){
		x=0;y=1;return b;
	}
	ll gcd=Exgcd(b%a,a,x,y);
	ll t=x;x=y-b/a*x;y=t;
	return gcd;
}

ll Mul(ll x,ll y,ll Mod){
	x=(x%Mod+Mod)%Mod;y=(y%Mod+Mod)%Mod;
	return (x*y-(ll)((ld)x/Mod*y+0.5)*Mod+Mod)%Mod;
}
