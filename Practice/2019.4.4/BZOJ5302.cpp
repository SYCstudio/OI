#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;

const int maxN=1010000;
const int Mod=1e9+7;

int n,Q,P;
int pcnt,Fp[100],pw[maxN],fcnt,Fc[5000],Cnt[5000];
map<int,int> Mp;

int main()
{
	pw[0]=1;
	for (int i=1; i<maxN; i++) pw[i]=2ll*pw[i-1]%Mod;
	scanf("%d%d%d",&n,&Q,&P);
	int X=P;
	for (int i=2; 1ll*i*i<=X; i++)
		if (X%i==0) {
			Fp[++pcnt]=i;
			while (X%i==0) X/=i;
		}
	if (X!=1) Fp[++pcnt]=X;
	X=P;
	for (int i=1; 1ll*i*i<=X; i++)
		if (X%i==0) {
			Fc[++fcnt]=i;
			if (X/i!=i) Fc[++fcnt]=X/i;
		}
	sort(&Fc[1],&Fc[fcnt+1]);
	for (int i=1; i<=fcnt; i++) Mp[Fc[i]]=i;

	for (int i=1; i<=n; i++) {
		int x;
		scanf("%d",&x);
		x=__gcd(x,P);
		++Cnt[Mp[x]];
	}

	//for (int i=1;i<=fcnt;i++) cout<<Fc[i]<<" ";cout<<endl;
	//for (int i=1;i<=fcnt;i++) cout<<Cnt[i]<<" ";cout<<endl;

	for (int i=1; i<=pcnt; i++) for (int j=fcnt; j>=1; j--) if (P%(1ll*Fc[j]*Fp[i])==0) Cnt[j]+=Cnt[Mp[Fc[j]*Fp[i]]];
	//for (int i=1;i<=fcnt;i++) cout<<Cnt[i]<<" ";cout<<endl;
	for (int i=1; i<=fcnt; i++) Cnt[i]=pw[Cnt[i]];
	for (int i=1; i<=pcnt; i++) for (int j=1; j<=fcnt; j++) if (P%(1ll*Fc[j]*Fp[i])==0) ((Cnt[j]-=Cnt[Mp[Fc[j]*Fp[i]]])+=Mod)%=Mod;
	//for (int i=1;i<=fcnt;i++) cout<<Cnt[i]<<" ";cout<<endl;
	for (int i=fcnt; i>=1; i--) for (int j=i-1; j>=1; j--) if (Fc[i]%Fc[j]==0) (Cnt[i]+=Cnt[j])%=Mod;

	while (Q--) {
		int w;
		scanf("%d",&w);
		w=__gcd(w,P);
		printf("%d\n",Cnt[Mp[w]]);
	}
	return 0;
}