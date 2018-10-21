#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int inf=2147483647;
const int Mod=1e9+7;

int n;
ll Arr[maxN];
ll Ret[maxN];
ll Fac[maxN],Sum[maxN],P[maxN];

int main()
{
	ll Ans=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Arr[i]);
	Fac[1]=1;for (int i=2;i<=n;i++) Fac[i]=Fac[i-1]*(ll)i%Mod;
	for (int i=2;i<=n;i++) Sum[i]=(Sum[i-1]+Fac[i])%Mod;
	sort(&Arr[1],&Arr[n+1]);
	for (int i=1;i<=n;i++)
	{
		if (Arr[i]==Arr[n]) break;
		if (Arr[i]==Arr[i-1]){
			Ret[i]=Ret[i-1];Ans=Ans+Ret[i];continue;
		}
	}
}
