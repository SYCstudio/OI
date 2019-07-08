#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=101000;
const int maxNum=1010000;
const int Mod=1e9+7;

int n,mx=0;
int F[maxNum],iF[maxNum],G[maxNum],use[maxNum],Mu[maxNum];

void Init(int mx);
int QPow(int x,int cnt);

int main()
{
	//freopen("in","r",stdin);
	scanf("%d",&n);
	for (int i=1,x; i<=n; i++) scanf("%d",&x),mx=max(mx,x),use[x]=1;
	for (int i=1; i<=mx; i++) for (int j=i+i; j<=mx; j+=i) use[i]|=use[j];
	Init(mx);
	int Ans=1;
	for (int i=1; i<=mx; i++) if (use[i]) Ans=1ll*Ans*G[i]%Mod;
	printf("%d\n",Ans);
	return 0;
}
void Init(int mx)
{
	F[0]=0;
	F[1]=1;
	iF[1]=1;
	for (int i=2; i<=mx; i++) F[i]=(F[i-1]+F[i-2])%Mod,iF[i]=QPow(F[i],Mod-2);
	for (int i=Mu[1]=1; i<=mx; i++) for (int j=i+i; j<=mx; j+=i) Mu[j]-=Mu[i];
	for (int i=1; i<=mx; i++) G[i]=1;
	for (int i=1; i<=mx; i++) for (int j=i; j<=mx; j+=i) Mu[j/i]==1?G[j]=1ll*G[j]*F[i]%Mod:(Mu[j/i]==-1?G[j]=1ll*G[j]*iF[i]%Mod:G[j]);

	//for (int i=1;i<=mx;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=1;i<=mx;i++) cout<<Mu[i]<<" ";cout<<endl;
	//for (int i=1;i<=mx;i++) cout<<G[i]<<" ";cout<<endl;
	return;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}