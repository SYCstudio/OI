#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

typedef long long ll;

map<ll,ll> P,Q;

ll Mul(ll x,ll y,ll M);
ll QPow(ll x,ll cnt,ll M);
void Fc(map<ll,ll> &M,ll X);
bool Miller_Rabin(ll X);
ll Polard_Rho(ll X);
int main(){
    int n;scanf("%d",&n);
    for (int i=1;i<=n;i++){
        ll X;scanf("%lld",&X);Fc(P,X);
    }
    for (int i=1;i<=n;i++){
        ll X;scanf("%lld",&X);Fc(Q,X);
    }
}
ll Mul(ll x,ll y,ll M){
    return (x*y-(ll)((long double)x/M*y+0.5)*M+M)%M;
}
ll QPow(ll x,ll cnt,ll M){
    ll ret=1;
    while (cnt){
        if (cnt&1) ret=Mul(ret,x,M);
        x=Mul(x,x,M);cnt>>=1;
    }
    return ret;
}
bool Miller_Rabin(ll X){
    static int pcnt=10,P[]={2,3,5,7,11,13,17,19,23,29};
    for (int i=0;i<10;i++){
        if (X<=P[i]) continue;
        if (QPow(P[i],X-1,X)!=1) return 0;
    }
}