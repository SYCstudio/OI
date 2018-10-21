#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=1e9+7;
const int inf=2147483647;

ll K,a,b;
ll F[maxN][maxN];

ll QPow(ll x,ll cnt);

int main()
{
	ios::sync_with_stdio(false);
	cin>>K>>a>>b;
	ll invab=QPow(a+b,Mod-2);
	ll inva=QPow(a,Mod-2),invb=QPow(b,Mod-2);
	for (int i=K;i>=0;i--)
		for (int j=K;j>=0;j--)
			if ((i!=0)||(j!=0))
			{
				if (i+j>=K) F[i][j]=(ll)(i+j)+(ll)a*invb%Mod;
				else F[i][j]=((ll)a*F[i][j+1]%Mod*invab%Mod+(ll)b*F[i+j][j]%Mod*invab%Mod)%Mod;
			}
	cout<<F[0][1]<<endl;
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
