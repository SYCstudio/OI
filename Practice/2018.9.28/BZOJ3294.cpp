#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=31;
const int maxC=12;
const int Mod=1e9+9;
const int inf=2147483647;

int n,m,c;
int Cnt[maxC];
ll F[maxC][maxN][maxN];
ll G[maxC][maxN][maxN];
ll C[1010][1010];

int main(){
	for (int i=0;i<=1000;i++)
		for (int j=C[i][0]=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	scanf("%d%d%d",&n,&m,&c);
	for (int i=1;i<=c;i++) scanf("%d",&Cnt[i]);

	for (int x=1;x<=c;x++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				if ((i*j<Cnt[x])||(max(i,j)>Cnt[x])) continue;
				G[x][i][j]=C[i*j][Cnt[x]];
				for (int p=1;p<=i;p++)
					for (int q=1;q<=((p==i)?(j-1):(j));q++)
						G[x][i][j]=(G[x][i][j]-1ll*G[x][p][q]*C[i][p]%Mod*C[j][q]%Mod+Mod)%Mod;
			}
	F[0][0][0]=1;
	for (int x=1;x<=c;x++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				if (i*j<Cnt[x]) continue;
				for (int p=0;p<i;p++)
					for (int q=0;q<j;q++)
						F[x][i][j]=(F[x][i][j]+1ll*F[x-1][p][q]*G[x][i-p][j-q]%Mod*C[i][p]%Mod*C[j][q]%Mod)%Mod;
			}
	ll Ans=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Ans=(Ans+1ll*F[c][i][j]*C[n][i]%Mod*C[m][j]%Mod)%Mod;
	printf("%lld\n",Ans);return 0;
}
