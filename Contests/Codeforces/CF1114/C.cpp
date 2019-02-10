#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

ll Calc(ll n,ll x);
int main(){
    ll n,B;cin>>n>>B;
    ll Ans=1e18;
    ll fB=B;
    for (ll i=2;(double)i*(double)i<=fB;i++)
        if (fB%i==0){
            ll cnt=Calc(n,i);ll count=0;
            while (fB%i==0) fB/=i,++count;
            Ans=min(Ans,cnt/count);
        }
    if (fB!=1){
        ll cnt=Calc(n,fB);
        Ans=min(Ans,cnt);
    }
    cout<<Ans<<endl;
    return 0;
}
ll Calc(ll n,ll x){
    ll ret=0;
    for (ll i=n;i;i/=x) ret+=i/x;
    return ret;
}