#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100;
const int inf=2147483647;

ll W[maxN];

ll Lucas(ll n,ll m,ll P);
ll Inv(ll n,ll P);
void Exgcd(ll a,ll b,ll &x,ll &y);
ll GetC(ll n,ll m,ll p,ll pk);
ll GetFac(ll n,ll p,ll pk);
ll QPow(ll x,ll cnt,ll P);

int main(){
	ll n,m,P;
	scanf("%lld",&P);
	scanf("%lld%lld",&n,&m);
	ll sum=0;
	for (int i=1;i<=m;i++) scanf("%lld",&W[i]),sum+=W[i];

	if (sum>n){
		printf("Impossible\n");
		return 0;
	}

	ll Ans=1;
	for (int i=1;i<=m;i++){
		Ans=Ans*Lucas(n,W[i],P)%P;
		n=n-W[i];
	}

	printf("%lld\n",Ans);

	return 0;
}

ll Lucas(ll n,ll m,ll P){
	if (n<m) return 0;
	ll ret=0,X=P;
	for (ll i=2;i<=X;i++)
		if (X%i==0){
			ll pk=1;
			while (X%i==0) X/=i,pk*=i;
			ll rt=GetC(n,m,i,pk);
			ret=(ret+rt*(P/pk)%P*Inv(P/pk,pk)%P)%P;
		}
	return ret;
}

ll Inv(ll n,ll P){
	ll x,y;
	Exgcd(n,P,x,y);
	x=(x%P+P)%P;
	return x;
}

void Exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){
		x=1;y=0;return;
	}
	Exgcd(b,a%b,x,y);
	ll t=x;x=y;y=t-a/b*y;return;
}

ll GetC(ll n,ll m,ll p,ll pk){
	if (n<m) return 0;
	ll a=GetFac(n,p,pk),b=GetFac(m,p,pk),c=GetFac(n-m,p,pk);
	ll pcnt=0;
	for (ll i=n;i;i/=p) pcnt+=i/p;
	for (ll i=m;i;i/=p) pcnt-=i/p;
	for (ll i=n-m;i;i/=p) pcnt-=i/p;
	return QPow(p,pcnt,pk)*a%pk*Inv(b,pk)%pk*Inv(c,pk)%pk;
}

ll GetFac(ll n,ll p,ll pk){
	if (n==0) return 1;
	ll ret=1;
	for (int i=1;i<=pk;i++) if (i%p) ret=ret*i%pk;
	ret=QPow(ret,n/pk,pk);
	for (int i=1;i<=n%pk;i++) if (i%p) ret=ret*i%pk;
	return ret*GetFac(n/p,p,pk)%pk;
}

ll QPow(ll x,ll cnt,ll P){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=ret*x%P;
		x=x*x%P;cnt>>=1;
	}
	return ret;
}
