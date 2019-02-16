#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=1000010;
const int Mod=1e9+7;
const int inf=2147483647;

int Mu[maxNum];
int pricnt=0,Prime[maxNum/100];
bool notprime[maxNum];
int Fab[maxNum],InvFab[maxNum];
int H[maxNum],InvH[maxNum];

void Init();
int QPow(ll x,ll cnt,ll Mod);
int Inv(ll x,ll Mod);

int main()
{
	Init();
	int T;scanf("%d",&T);
	while (T--)
	{
		ll n,m;scanf("%lld%lld",&n,&m);if (n>m) swap(n,m);
		ll ans=1;
		for (ll i=1,last;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans=ans*QPow((ll)H[last]*(ll)InvH[i-1]%Mod,(ll)(n/i)*(ll)(m/i)%(Mod-1),Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

void Init()
{
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Mu[i]=-1,Prime[++pricnt]=i;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	Fab[0]=0;Fab[1]=1;H[0]=InvH[0]=1;
	for (int i=2;i<maxNum;i++) Fab[i]=(Fab[i-1]+Fab[i-2])%Mod;
	//for (int i=1;i<=10;i++) cout<<Fab[i]<<" ";cout<<endl;
	for (int i=1;i<maxNum;i++) InvFab[i]=Inv(Fab[i],Mod),H[i]=1;
	for (int i=1;i<maxNum;i++)
		if (Mu[i]!=0)
			for (int j=i;j<maxNum;j=j+i)
				H[j]=(ll)H[j]*(ll)((Mu[i]==1)?(Fab[j/i]):(InvFab[j/i]))%Mod;
	//cout<<"T"<<endl;
	for (int i=1;i<maxNum;i++) InvH[i]=Inv(H[i],Mod);
	//cout<<"TT"<<endl;
	for (int i=2;i<maxNum;i++) H[i]=(ll)H[i]*(ll)H[i-1]%Mod,InvH[i]=(ll)InvH[i]*(ll)InvH[i-1]%Mod;
	return;
}

int QPow(ll x,ll cnt,ll Mod)
{
	ll ret=1;
	while (cnt)
	{
		if (cnt&1) ret=ret*x%Mod;
		x=x*x%Mod;
		cnt=cnt>>1;
	}
	return ret%Mod;
}

int Inv(ll x,ll Mod)
{
	return QPow(x,Mod-2,Mod)%Mod;
}
