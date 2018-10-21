#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int maxM=15;
const int Mod=1000000000;
const int inf=2147483647;

int n,m;
int C[maxN];
ll F[maxN][1<<(maxM+1)];
ll Sum[1<<(maxM+1)];

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while (T--)
	{
		cin>>n>>m;
		for (int i=1;i<=n;i++) cin>>C[i];
		mem(F,0);mem(Sum,0);
		for (int i=0;i<(1<<m);i++) if (i%C[1]!=0) F[1][i]=Sum[i]=1;
		for (int i=0;i<m;i++)
			for (int j=0;j<(1<<m);j++)
				if ((j&(1<<i))!=0) Sum[j]=(Sum[j]+Sum[j^(1<<i)])%Mod;
		for (int i=2;i<=n;i++)
		{
			for (int j=0;j<(1<<m);j++) if (j%C[i]!=0) F[i][j]=Sum[j^((1<<m)-1)];
			mem(Sum,0);
			for (int j=0;j<(1<<m);j++) Sum[j]=F[i][j];
			for (int j=0;j<m;j++)
				for (int k=0;k<(1<<m);k++)
					if ((k&(1<<j))!=0) Sum[k]=(Sum[k]+Sum[k^(1<<j)])%Mod;
		}
		ll Ans=0;
		for (int i=0;i<(1<<m);i++) if (i%C[n]!=0) Ans=(Ans+F[n][i])%Mod;
		printf("%lld\n",Ans);
	}
	return 0;
}
