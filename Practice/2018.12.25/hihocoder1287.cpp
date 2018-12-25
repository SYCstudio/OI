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
		ll x;scanf("%lld",&x);
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
	static int pcnt=13,P[]={2,3,5,7,9,11,13,17,19,23,29,31,37};
	ll xx=x-1;while (xx%2==0) xx/=2;
	//cout<<"MR:"<<x<<" "<<xx<<endl;
	for (int i=0;i<pcnt;i++){
		if (P[i]>=x) continue;
		ll a=QPow(P[i],xx,x),b,nowx=xx;
		//cout<<a<<endl;
		while (nowx<x){
			b=Mul(a,a,x);
			if (b==1)
				if ((a!=1)&&(a!=x-1)) return 0;
			a=b;nowx=nowx*2;
		}
		if (a!=1) return 0;
	}
	return 1;
}
