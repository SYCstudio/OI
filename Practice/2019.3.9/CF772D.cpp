#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=1000100;
const int Num=999999;
const int Mod=1e9+7;

int n;
int Sm1[maxN],Sm2[maxN],Sm3[maxN];

void Plus(int &x,int y);
void Minus(int &x,int y);
int QPow(int x,int cnt);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		int x;
		scanf("%d",&x);
		++Sm3[x];
	}
	for (int i=0; i<=Num; i++) Sm1[i]=1ll*Sm3[i]*i%Mod,Sm2[i]=1ll*Sm3[i]*i%Mod*i%Mod;
	for (int k=8; k>=0; k--)
		for (int i=0,mul=1; i<=5; i++,mul=mul*10)
			for (int j=0; j<=Num; j++)
				if (j/mul%10==k) Plus(Sm1[j],Sm1[j+mul]),Plus(Sm2[j],Sm2[j+mul]),Plus(Sm3[j],Sm3[j+mul]);
	int inv2=QPow(2,Mod-2);
	for (int i=0; i<=Num; i++) {
		if (!Sm3[i]) continue;
		int pw=QPow(2,Sm3[i]-1);
		int k=(1ll*Sm1[i]*Sm1[i]%Mod+Sm2[i])%Mod;
		Sm1[i]=1ll*k*pw%Mod*inv2%Mod;
	}
	for (int k=0; k<=8; k++)
		for (int i=0,mul=1; i<=5; i++,mul=mul*10)
			for (int j=0; j<=Num; j++)
				if (j/mul%10==k) Minus(Sm1[j],Sm1[j+mul]);
	ll Ans=0;
	for (int i=0; i<=Num; i++) Ans=Ans^(1ll*Sm1[i]*i);
	printf("%lld\n",Ans);
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}
void Minus(int &x,int y)
{
	x-=y;
	if (x<0) x+=Mod;
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