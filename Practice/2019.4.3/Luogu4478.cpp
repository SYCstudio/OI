#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=220;

int F[maxN];

int Binom(ll n,ll m,int Mod);
int Inv(ll x,int Mod);
int QPow(ll x,int cnt,int P);
namespace M1
{
const int Mod=1000003;
int Fc[Mod+5],Ifc[Mod+5];
void Init();
int Binom(ll n,ll m);
}
namespace M2
{
const int Mod=1019663265;
const int P[]= {3,5,6793,10007};
int Fc[4][20000],Ifc[4][20000];
void Init();
int Binom(ll n,ll m);
int GetC(ll n,ll m,int pid);
}

int main()
{
	int T,Mod;
	ll n,m;
	pair<ll,ll> P[maxN];
	scanf("%lld%lld%d%d",&n,&m,&T,&Mod);
	if (Mod==M1::Mod) M1::Init();
	else M2::Init();
	for (int i=1; i<=T; i++) scanf("%lld%lld",&P[i].first,&P[i].second);
	sort(&P[1],&P[T+1]);
	//for (int i=1;i<=T;i++) cout<<"("<<P[i].first<<","<<P[i].second<<") ";cout<<endl;
	for (int i=1; i<=T; i++) {
		F[i]=Binom(P[i].first+P[i].second,P[i].first,Mod);
		for (int j=1; j<i; j++)
			if (P[j].first<=P[i].first&&P[j].second<=P[i].second) {
				F[i]=(F[i]-1ll*F[j]*Binom(P[i].first-P[j].first+P[i].second-P[j].second,P[i].first-P[j].first,Mod)%Mod+Mod)%Mod;
			}
	}
	int Ans=Binom(n+m,m,Mod);
	for (int i=1; i<=T; i++) if (P[i].first<=n&&P[i].second<=m) Ans=(Ans-1ll*F[i]*Binom(n-P[i].first+m-P[i].second,n-P[i].first,Mod)%Mod+Mod)%Mod;
	printf("%d\n",Ans);
	return 0;
}
int Binom(ll n,ll m,int Mod)
{
	if (Mod==M1::Mod) return M1::Binom(n,m);
	else return M2::Binom(n,m);
}
int Inv(ll x,int Mod)
{
	return QPow(x,Mod-2,Mod);
}
int QPow(ll x,int cnt,int P)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%P;
		x=1ll*x*x%P;
		cnt>>=1;
	}
	return ret;
}
namespace M1
{
void Init()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<Mod; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[Mod-1]=Inv(Fc[Mod-1],Mod);
	for (int i=Mod-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	return;
}
int Binom(ll n,ll m)
{
	if (n<0||m<0||n<m) return 0;
	if (n<Mod&&m<Mod) return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
	return 1ll*Binom(n%Mod,m%Mod)*Binom(n/Mod,m/Mod)%Mod;
}
}
namespace M2
{
void Init()
{
	for (int i=0; i<4; i++) {
		Fc[i][0]=Ifc[i][0]=1;
		for (int j=1; j<P[i]; j++) Fc[i][j]=1ll*Fc[i][j-1]*j%P[i];
		Ifc[i][P[i]-1]=Inv(Fc[i][P[i]-1],P[i]);
		for (int j=P[i]-2; j>=1; j--) Ifc[i][j]=1ll*Ifc[i][j+1]*(j+1)%P[i];
	}
	return;
}
int Binom(ll n,ll m)
{
	int ret=0;
	for (int i=0; i<4; i++)
		ret=(ret+1ll*GetC(n,m,i)*Inv(Mod/P[i],P[i])%Mod*(Mod/P[i])%Mod)%Mod;
	return ret;
}
int GetC(ll n,ll m,int i)
{
	if (n<0||m<0||n<m) return 0;
	if (n<P[i]&&m<P[i]) return 1ll*Fc[i][n]*Ifc[i][m]%P[i]*Ifc[i][n-m]%P[i];
	return 1ll*GetC(n/P[i],m/P[i],i)*GetC(n%P[i],m%P[i],i)%P[i];
}
}