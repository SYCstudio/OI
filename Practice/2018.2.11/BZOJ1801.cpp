#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int Mod=9999973;
const int inf=2147483647;

int n,m;
ll F[maxN][maxN][maxN];

ll QPow(ll x,ll cnt);

int main()
{
	int inv2=QPow(2,Mod-2);
	scanf("%d%d",&n,&m);
	F[0][m][0]=1;
	for (ll i=0;i<n;i++)
		for (ll p1=0;p1<=m;p1++)
			for (ll p2=0;p1+p2<=m;p2++)
			{
				if (F[i][p1][p2]==0) continue;
				F[i+1][p1][p2]=(F[i+1][p1][p2]+F[i][p1][p2])%Mod;//什么都不放
				if (p1>=1) F[i+1][p1-1][p2+1]=(F[i+1][p1-1][p2+1]+F[i][p1][p2]*(ll)p1%Mod)%Mod;//在空的某一列摆上一个
				if (p2>=1) F[i+1][p1][p2-1]=(F[i+1][p1][p2-1]+F[i][p1][p2]*(ll)p2%Mod)%Mod;//在有一个的某一列摆上一个
				if (p1>=2) F[i+1][p1-2][p2+2]=(F[i+1][p1-2][p2+2]+1ll*F[i][p1][p2]*p1%Mod*(p1-1ll)%Mod*inv2%Mod)%Mod;//在两列空的上面分别摆上一个
				if (p2>=2) F[i+1][p1][p2-2]=(F[i+1][p1][p2-2]+1ll*F[i][p1][p2]*p2%Mod*(p2-1ll)%Mod*inv2%Mod)%Mod;//在两个已经摆了一个的上面再分别摆一个
				if ((p1>=1)&&(p2>=1)) F[i+1][p1-1][p2]=(F[i+1][p1-1][p2]+1ll*F[i][p1][p2]*p1%Mod*p2%Mod)%Mod;//在空列和摆了一个的一列摆上一个
			}
	int Ans=0;
	for (int p1=0;p1<=m;p1++)
		for (int p2=0;p1+p2<=m;p2++)
			Ans=(Ans+F[n][p1][p2])%Mod;
	printf("%d\n",Ans);
	return 0;
}

ll QPow(ll x,ll cnt)
{
	ll ret=1;
	while (cnt)
	{
		if (cnt&1) ret=ret*x%Mod;
		x=x*x%Mod;
		cnt=cnt>>1;
	}
	return ret;
}
