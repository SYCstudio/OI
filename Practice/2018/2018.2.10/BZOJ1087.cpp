#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10;
const int inf=2147483647;

int n,K;
ll F[maxN][maxN*maxN][1<<maxN];
bool Put[1<<maxN];//标记某一种状态是否可行
int Num[1<<maxN];//某一状态摆了多少个王

int main()
{
	scanf("%d%d",&n,&K);
	for (int i=0;i<(1<<n);i++)
		if ((i&(i<<1))==0)
		{
			Put[i]=1;
			for (int j=0;j<n;j++) if (((1<<j)&i)!=0) Num[i]++;
			F[1][Num[i]][i]=1;
		}
	for (int i=2;i<=n;i++)
		for (int j=0;j<=K;j++)
			for (int S=0;S<(1<<n);S++)
				if (Put[S]==1)
					for (int S2=0;S2<(1<<n);S2++)
						if ((Put[S2]==1)&&((S&S2)==0)&&(j-Num[S]>=0)&&((S&(S2<<1))==0)&&(((S<<1)&S2)==0))
							F[i][j][S]=(F[i][j][S]+F[i-1][j-Num[S]][S2]);
	ll Ans=0;
	for (int i=0;i<(1<<n);i++) Ans=Ans+F[n][K][i];
	printf("%lld\n",Ans);
	return 0;
}
