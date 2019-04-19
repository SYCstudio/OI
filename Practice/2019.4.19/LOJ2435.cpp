#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a,ll b);
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
	ll K,n;scanf("%lld%lld",&n,&K);ll Ans=K,m=1,up=K-1;
	while (up){
	    ll d=gcd(n,K),t=K/d;
	    if (d==1||up<=t) break;
	    Ans=Ans-(up-t);
	    if (t/m/(n/d)==0) break;
	    m=m*(n/d);up=t-m;K=K/d;
	}
	printf("%lld\n",Ans);
    }
    return 0;
}
ll gcd(ll a,ll b){
    if (!a||!b) return a|b;
    int t=__builtin_ctzll(a|b);ll tmp;
    a>>=__builtin_ctzll(a);
    do{
        b>>=__builtin_ctzll(b);
        if (a>b) tmp=a,a=b,b=tmp;b-=a;
    }
    while (b);
    return a<<t;
}
