#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

map<ll,int> M;

ll Exgcd(ll a,ll b,ll &x,ll &y);
ll QPow(ll x,ll cnt,ll P);

int main(){
	int T,K;
	scanf("%d%d",&T,&K);
	while (T--){
		ll a,b,p;scanf("%lld%lld%lld",&a,&b,&p);
		if (K==1) printf("%lld\n",QPow(a,b,p));
		if (K==2){
			ll x,y;
			ll gcd=Exgcd(a,p,x,y);
			if (b%gcd) printf("Orz, I cannot find x!\n");
			else{
				x=x*(b/gcd);
				x=(x%p+p)%p;
				printf("%lld\n",x);
			}
		}
		if (K==3){
			if (a%p==0){
				printf("Orz, I cannot find x!\n");
				continue;
			}
			M.clear();
			ll m=ceil(sqrt(p)),now=b,t=1;
			M[now]=0;
			for (int i=1;i<=m;i++){
				now=now*a%p;t=t*a%p;
				M[now]=i;
			}
			now=1;bool getans=0;
			for (int i=1;i<=m;i++){
				now=now*t%p;
				if (M.count(now)){
					ll ans=1ll*i*m-M[now];
					ans=(ans%p+p)%p;getans=1;
					printf("%lld\n",ans);
					break;
				}
			}

			if (getans==0) printf("Orz, I cannot find x!\n");
		}
	}

	return 0;
}

ll Exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){
		x=1;y=0;return a;
	}
	ll g=Exgcd(b,a%b,x,y);
	ll t=x;x=y;y=t-a/b*y;
	return g;
}

ll QPow(ll x,ll cnt,ll P){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=ret*x%P;
		x=x*x%P;cnt>>=1;
	}
	return ret;
}
