#include<cstdio>
#include<cstdlib>
using namespace std;

#define ll long long
#define RG register

ll Ans=0;

__attribute__((always_inline)) ll Mul(ll a,ll b,ll Mod);
__attribute__((always_inline)) ll QPow(ll x,ll cnt,ll Mod);
__attribute__((always_inline)) bool MR(ll x);
void PR(ll x);
__attribute__((always_inline)) ll gcd(ll a,ll b);
__attribute__((always_inline)) ll f(ll x,ll k,ll Mod);

int main(){
	freopen("in","r",stdin);freopen("out","w",stdout);
	srand(20020729);
	int Case;scanf("%d",&Case);
	while (Case--){
		ll x;scanf("%lld",&x);
		//cerr<<x<<endl;
		if (MR(x)) printf("Prime\n");
		else Ans=0,PR(x),printf("%lld\n",Ans);
	}
	return 0;
}

__attribute__((always_inline)) ll gcd(ll a,ll b){
	//cerr<<"getgcd:"<<a<<" "<<b<<endl;
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

/*
__attribute__((always_inline)) ll Mul(ll a,ll b,ll Mod){
	return (__int128)a*(__int128)b%Mod;
}
//*/

__attribute__((always_inline)) ll Mul(ll a,ll b,ll p){
    ll d=((long double)a/p*b+1e-8);
    ll r=a*b-d*p;
    return r<0?r+p:r;
}

__attribute__((always_inline)) ll QPow(ll x,ll cnt,ll Mod){
	RG ll ret=1;
	while (cnt){
		if (cnt&1) ret=Mul(ret,x,Mod);
		x=Mul(x,x,Mod);cnt>>=1;
	}
	return ret;
}

__attribute__((always_inline)) bool MR(ll x){
	if (x<=2) return x==2;
	if (!(x&1)) return 0;
	ll xx=x-1;while (!(xx&1)) xx/=2;
	static int P[]={2,3,7,11,13};
	for (int i=0;i<5;i++){
		if (P[i]>=x) continue;
		ll a=QPow(P[i],xx,x),b,nowx=xx;
		while (nowx<x){
			b=Mul(a,a,x);
			if (b==1) if ((a!=1)&&(a!=x-1)) return 0;
			a=b;nowx=nowx*2;
		}
		if (a!=1) return 0;
	}
	return 1;
}

void PR(ll x){
	//cerr<<x<<endl;
	if (Ans>=x) return;
	if ((x==1)||(x==2)||(x==3)||(x==5)||(x==7)) return Ans=x,(void(0));
	if (MR(x)) return Ans=x,(void(0));
	do{
		ll k=rand()%x,a=k,b=f(a,k,x),g;
		if (a&&(x%a==0)) return PR(a),PR(x/a),(void(0));
		if (b&&(x%b==0)) return PR(b),PR(x/b),(void(0));
		while (a!=b){
			g=gcd(abs(a-b),x);
			//if (g!=1) cerr<<g<<" "<<x/g<<endl;
			if (g!=1) return PR(g),PR(x/g),(void(0));
			a=f(a,k,x);b=f(f(b,k,x),k,x);//a=(Mul(a,a,x)+k);if (a>=x) a-=x;
			//b=(Mul(b,b,x)+k);if (b>=x) b-=x;
			//b=(Mul(b,b,x)+k);if (b>=x) b-=x;
		}
	}
	while (1);
}

__attribute__((always_inline)) ll f(ll x,ll k,ll Mod){
	x=Mul(x,x,Mod)+k;if (x>=Mod) x-=Mod;
	return x;
}
