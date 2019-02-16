#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;

#define ll long long

const int Mod2=512;
const int Mod5=1953125;
const int MM=1e9;

int Num[Mod5];
int P[2]={2,5},PM[2]={Mod2,Mod5};
int Fac[2][Mod5+10],Fc[2][Mod5+10];
int fcnt=0;
map<ll,int> Mp[2];

int QPow(int x,ll cnt,int Mod);
int GetInv(int x,int p);
void Exgcd(int a,int b,int &x,int &y);
int Calc(ll n,ll m,bool div2);
int C(ll n,ll m,int pid,bool div2);
int GetFac(ll n,int pid);

int main(){
	Num[1]=1;for (int i=2;i<Mod2;i++) Num[i]=(i%2)?(i):(Num[i/2]);
	Fac[0][0]=Fc[0][0]=1;
	for (int i=1;i<Mod2;i++) Fac[0][i]=1ll*Fac[0][i-1]*((i%2)?i:1)%Mod2,Fc[0][i]=1ll*Fc[0][i-1]*Num[i]%Mod2;
	Num[1]=1;for (int i=2;i<Mod5;i++) Num[i]=(i%5)?(i):(Num[i/5]);
	Fac[1][0]=Fc[1][0]=1;
	for (int i=1;i<Mod5;i++) Fac[1][i]=1ll*Fac[1][i-1]*((i%5)?i:1)%Mod5,Fc[1][i]=1ll*Fc[1][i-1]*Num[i]%Mod5;

	//for (ll i=1;i<1e18;i=i*2) cout<<GetFac(i,0)<<" ";cout<<endl;
	//for (ll i=1;i<1e18;i=i*5ll) cout<<GetFac(i,1)<<" ";cout<<endl;
	
	ll a,b,K;
	while (scanf("%lld%lld%lld",&a,&b,&K)!=EOF){
		ll Ans=0;
		if (a==b) Ans=(QPow(2,a+b-1,MM)-Calc(a+b,a,1)%MM+MM)%MM;
		else{
			Ans=QPow(2,a+b-1,MM);
			if ((a-b-1)&1) Ans=(Ans+Calc(a+b,(a+b)/2,1)%MM+MM)%MM;
			for (ll i=b+1;i<=(a+b-1)/2;i++) Ans=(Ans+Calc(a+b,i,0)%MM+MM)%MM;
		}
		Ans%=MM;
		char buf[10];sprintf(buf,"%%0%lldlld\n",K);
		printf(buf,Ans);

		//cerr<<fcnt<<endl;
	}
	return 0;
}

int QPow(int x,ll cnt,int Mod){
	if (x==0) return 0;
	if (x==1) return 1;
	int ret=1;x%=Mod;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int GetInv(int x,int p){
	int e,f;
	Exgcd(x,p,e,f);
	e=(e%p+p)%p;
	return e;
}

void Exgcd(int a,int b,int &x,int &y){
	if (b==0){
		x=1;y=0;return;
	}
	Exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;return;
}

const ll k2=109,k5=1537323,inv=976563;

int Calc(ll n,ll m,bool div2){
	if (n<m) return 0;
	int a2=C(n,m,0,div2)%MM,a5=C(n,m,1,div2)%MM;
	//ll k2=GetInv(Mod5,Mod2),k5=GetInv(Mod2,Mod5);
	a2=1ll*a2*Mod5%MM*k2%MM;
	a5=1ll*a5*Mod2%MM*k5%MM;
	return (a2+a5)%MM;
}

int C(ll n,ll m,int pid,bool div2){
	int a=GetFac(n,pid),b=GetInv(GetFac(n-m,pid),PM[pid]),c=GetInv(GetFac(m,pid),PM[pid]);
	int cnt=0;
	for (ll i=n;i;i/=P[pid]) cnt+=i/P[pid];
	for (ll i=m;i;i/=P[pid]) cnt-=i/P[pid];
	for (ll i=n-m;i;i/=P[pid]) cnt-=i/P[pid];
	if ((div2)&&(pid==0)) --cnt;
	int ret=1ll*a*b%PM[pid]*c%PM[pid]*QPow(P[pid],cnt,PM[pid])%PM[pid];
	if ((div2)&&(pid==1)) ret=ret*inv%PM[pid];
	return ret;
}

int GetFac(ll n,int pid){
	++fcnt;
	if (n<PM[pid]) return Fc[pid][n];
	if (Mp[pid].count(n)) return Mp[pid][n];
	int ret=1;//,pk=PM[pid],p=P[pid];
	ret=QPow(Fac[pid][PM[pid]-1],n/PM[pid],PM[pid]);
	ret=1ll*ret*Fac[pid][n%PM[pid]]%PM[pid];
	return Mp[pid][n]=1ll*ret*GetFac(n/P[pid],pid)%PM[pid];
}
