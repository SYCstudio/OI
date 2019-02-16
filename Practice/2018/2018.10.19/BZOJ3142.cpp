#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

ll n,m,K,P;

ll QPow(ll x,ll cnt);

int main(){
	scanf("%lld%lld%lld%lld",&n,&K,&m,&P);
	ll s1=n%P*QPow(m,K-1)%P;
	ll s2=m*(m+1)/2%P*(K-1)%P*QPow(m,K-2)%P;
	printf("%lld\n",(s1-s2+P)%P);
}

ll QPow(ll x,ll cnt){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=ret*x%P;
		x=x*x%P;cnt>>=1;
	}
	return ret;
}
