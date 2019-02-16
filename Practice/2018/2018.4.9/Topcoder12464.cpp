#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=52;
const int Mod=1e9+7;
const int maxPos=100001*2;
const int inf=2147483647;

ll QPow(ll x,ll cnt)
{
	ll Ret=1;
	while (cnt)
	{
		if (cnt&1) Ret=Ret*x%Mod;
		x=x*x%Mod;
		cnt=cnt>>1;
	}
	return Ret;
}

class WolfPack
{
	int X[maxN],Y[maxN];
	ll Inv[maxPos*2+10],Fac[maxPos*2+10];
public:
	ll GetC(ll n,ll m){
		return Fac[n]*Inv[n-m]%Mod*Inv[m]%Mod;
	}
	int calc(vector<int> x, vector<int> y, int m){
		Fac[0]=Inv[0]=1;
		for (int i=1;i<=maxPos*2;i++)
		{
			Fac[i]=Fac[i-1]*(ll)i%Mod;
			Inv[i]=QPow(Fac[i],Mod-2);
		}
		int n=x.size();
		for (int i=0;i<n;i++)
		{
			X[i+1]=x[i]-y[i];
			Y[i+1]=x[i]+y[i];
		}
		ll Ans1=0,Ans2=0;
		for (int px=-maxPos;px<=maxPos;px++)
		{
			bool flag=1;
			for (int i=1;i<=n;i++)
				if (((abs(X[i]-px)&1)!=(m&1))||(abs(X[i]-px)>m))
				{
					flag=0;
					break;
				}
			if (flag==0) continue;
			ll now=1;
			for (int i=1;i<=n;i++)
			{
				int d=m-abs(X[i]-px);
				now=now*GetC(m,d/2)%Mod;
			}
			Ans1=(Ans1+now)%Mod;
		}
		for (int py=-maxPos;py<=maxPos;py++)
		{
			bool flag=1;
			for (int i=1;i<=n;i++)
				if (((abs(Y[i]-py)&1)!=(m&1))||(abs(Y[i]-py)>m))
				{
					flag=0;
					break;
				}
			if (flag==0) continue;
			ll now=1;
			for (int i=1;i<=n;i++)
			{
				int d=m-abs(Y[i]-py);
				now=now*GetC(m,d/2)%Mod;
			}
			Ans2=(Ans2+now)%Mod;
		}
		return Ans1*Ans2%Mod;
	}
}Do;

int X[]={-2,-2,-2,0,0,0,2,2,2};
int Y[]={-2,0,2,-2,0,2,-2,0,2};
vector<int> Inx(X,X+9);
vector<int> Iny(Y,Y+9);
int Limit=1000;

int main()
{
	cout<<Do.calc(Inx,Iny,Limit)<<endl;
	return 0;
}
