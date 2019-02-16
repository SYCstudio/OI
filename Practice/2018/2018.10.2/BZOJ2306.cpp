#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ld long double
#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const ld eps=1e-8;
const int inf=2147483647;

int n,m,S;
ld F[maxN][maxN],G[maxN][maxN],W[maxN],P;

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%LF",&W[i]);
	scanf("%d",&S);scanf("%LF",&P);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) F[i][j]=((i==j)?(0):(-inf));
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		F[u][v]=W[v]*P;
	}
	for (ld p=P;p>eps;p*=p){
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) G[i][j]=-inf;
		for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					G[i][j]=max(G[i][j],F[i][k]+F[k][j]*p);
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) F[i][j]=max(F[i][j],G[i][j]);
	}
	ld Ans=0;
	for (int i=1;i<=n;i++) Ans=max(Ans,F[S][i]);
	printf("%.1LF\n",Ans+W[S]);return 0;
}
