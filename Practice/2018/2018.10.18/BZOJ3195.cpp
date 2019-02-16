#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=32;
const int maxM=32;
const int maxK=9;
const int Mod=1000000007;
const int inf=2147483647;

int n,m,K;
int F[maxN][maxM][1<<maxK][maxK];

void Plus(int &x,int y);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	F[2][0][0][0]=1;
	for (int i=2;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int S=0;S<(1<<(K+1));S++){
				for (int l=0;l<K;l++)
					if (F[i][j][S][l]){
						Plus(F[i][j][S][l+1],F[i][j][S][l]);
						if ((j!=m)&&(i-K+l>=1)) Plus(F[i][j+1][S^(1<<l)^(1<<K)][l],F[i][j][S][l]);
					}
				if (F[i][j][S][K]&&((S&1)==0)) Plus(F[i+1][j][S>>1][0],F[i][j][S][K]);
			}
	printf("%d\n",F[n+1][m][0][0]);
	return 0;
}

void Plus(int &x,int y){
	x=x+y;if (x>=Mod) x-=Mod;return;
}
