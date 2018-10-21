#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100;
const int maxK=210;
const int inf=147483647;

int n,m;
int A[maxN];
ll F[4][maxN][maxK];

void Max(ll &x,ll y);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	for (int i=0;i<=n;i++) for (int j=0;j<=m;j++) F[0][i][j]=F[1][i][j]=F[2][i][j]=F[3][i][j]=-inf;
	for (int i=0;i<=n;i++) F[0][i][0]=F[1][i][0]=F[2][i][0]=F[3][i][0]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=min(i,m);j++){
			int k=((j!=1)&&(j!=m));
			F[0][i][j]=max(F[0][i-1][j],F[3][i-1][j-1])-(k+1)*A[i];
			F[1][i][j]=max(F[1][i-1][j],F[2][i-1][j-1])+(k+1)*A[i];
			F[2][i][j]=max(F[2][i-1][j],F[0][i][j]);
			F[3][i][j]=max(F[3][i-1][j],F[1][i][j]);
			if (k){
				F[2][i][j]=max(F[2][i][j],F[2][i-1][j-1]);
				F[3][i][j]=max(F[3][i][j],F[3][i-1][j-1]);
			}
		}

	printf("%lld\n",max(F[2][n][m],F[3][n][m]));

	return 0;
}

void Max(ll &x,ll y){
	x=max(x,y);return;
}
