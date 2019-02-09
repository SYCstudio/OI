#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main(){
    ll K,A,B;scanf("%lld%lld%lld",&K,&A,&B);
    ll Ans=K+1;
    if (K>=A+1){
        ll base=B;K=K-A-1;
        ll cnt=K/2;base=base+cnt*(B-A);
        if (K%2==1) base++;
        Ans=max(Ans,base);
    }
    printf("%lld\n",Ans);
    return 0;
}