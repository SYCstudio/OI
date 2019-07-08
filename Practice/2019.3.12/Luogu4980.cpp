#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int Mod=1e9+7;
int pcnt,P[101000],Pc[101000];
int Ans,n;

int QPow(int x,int cnt);
void dfs(int d,int mul,int phi);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d",&n);
		Ans=pcnt=0;
		int X=n;
		for (int i=2; 1ll*i*i<=X; i++)
			if (X%i==0) {
				P[++pcnt]=i;
				Pc[pcnt]=0;
				while (X%i==0) X/=i,++Pc[pcnt];
			}
		if (X!=1) P[++pcnt]=X,Pc[pcnt]=1;
		dfs(1,1,n);
		Ans=1ll*Ans*QPow(n,Mod-2)%Mod;
		printf("%d\n",Ans);
	}
	return 0;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*x*ret%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
void dfs(int d,int mul,int phi)
{
	if (d==pcnt+1) {
		Ans=(Ans+1ll*QPow(n,mul)*phi%Mod)%Mod;
		return;
	}
	for (int i=0; i<Pc[d]; i++) dfs(d+1,mul,phi/P[d]*(P[d]-1)),mul*=P[d],phi/=P[d];
	dfs(d+1,mul,phi);
	return;
}