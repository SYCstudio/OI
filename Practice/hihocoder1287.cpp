#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll Mul(ll a,ll b,ll Mod);
ll QPow(ll x,ll cnt,ll Mod);
bool MR(ll x);

int main(){
	int Case;scanf("%d",&Case);
	while (Case--){
		ll x;scanf("%d",&x);
		if (MR(x)) printf("Yes\n");
		else printf("No\n");
	}
}

ll Mul(ll a,ll b,ll Mod){
	return (__int128)a*(__int128)b%Mod;
}

ll QPow(ll x,ll cnt,ll Mod){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=Mul(ret,x,Mod);
		x=Mul(x,x,Mod);cnt>>=1;
	}
	return ret;
}

bool MR(ll x){
	if (x<=2) return x==2;
	if (x%2==0) return 0;
}
