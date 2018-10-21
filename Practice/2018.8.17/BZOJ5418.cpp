#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n,m;
ll A[maxN],P[maxN],Sword[maxN];
ll X[maxN],M[maxN];
multiset<ll> Ms;

ll Gcd(ll a,ll b);
ll Exgcd(ll a,ll b,ll &x,ll &y);
ll Mul(ll x,ll y,ll Mod);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&n,&m);
		Ms.clear();
		for (int i=1;i<=n;i++) scanf("%lld",&A[i]);
		for (int i=1;i<=n;i++) scanf("%lld",&P[i]);
		for (int i=1;i<=n;i++) scanf("%lld",&Sword[i]);
		for (int i=1;i<=m;i++){
			int key;scanf("%d",&key);Ms.insert(key);
		}
		
		bool flag=1;ll limit=0;
		for (int i=1;i<=n;i++){
			multiset<ll>::iterator p;
			if ((*Ms.begin())>=A[i]) p=Ms.begin();
			else if ((*--Ms.end())<=A[i]) p=--Ms.end();
			else{
				p=Ms.lower_bound(A[i]);
				if ((*p)>A[i]) p--;
			}

			//cout<<"nowset:";for (multiset<ll>::iterator it=Ms.begin();it!=Ms.end();it++) cout<<(*it)<<" ";cout<<endl;
			//cout<<"choose:"<<i<<" "<<A[i]<<" "<<(*p)<<endl;

			limit=max(limit,(A[i]+(*p)-1)/(*p));
			ll x,y;
			ll gcd=Gcd((*p),P[i]);
			Exgcd((*p)/gcd,P[i]/gcd,x,y);
			if (A[i]%gcd!=0){
				flag=0;break;
			}
			x=Mul(x,A[i]/gcd,P[i]/gcd);
			X[i]=x;M[i]=P[i]/gcd;

			//cout<<X[i]<<" "<<M[i]<<endl;

			Ms.erase(p);Ms.insert(Sword[i]);
		}

		if (flag==0){
			printf("-1\n");continue;
		}

		for (int i=2;i<=n;i++){
			ll x,y,gcd=Gcd(M[1],M[i]),dt=X[i]-X[1];
			ll P=M[1]/gcd*M[i];dt=(dt%P+P)%P;
			Exgcd(M[1]/gcd,M[i]/gcd,x,y);
			if (abs(dt)%gcd!=0){
				flag=0;break;
			}
			ll t=M[i]/gcd;
			x=(x%M[i]+M[i])%M[i];
			x=Mul(x,dt/gcd,M[i]);
			X[1]=(X[1]%P+Mul(x,M[1],P))%P;
			M[1]=P;
		}

		if (flag==0){
			printf("-1\n");continue;
		}
		
		ll Ans=X[1];
		if (Ans<limit) Ans=Ans+(limit-Ans+M[1]-1)/M[1];
		printf("%lld\n",Ans);
	}

	return 0;
}

ll Gcd(ll a,ll b){
	if (a==0) return b;
	return Gcd(b%a,a);
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
