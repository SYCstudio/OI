#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1510;
const int inf=2147483647;

int n,m,K;
int Val[maxN][maxN];
int F[3][maxN][maxN],G[3][maxN][maxN];

int Get(int x1,int y1,int x2,int y2);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Val[i][j]);

	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Val[i][j]=Val[i][j]+Val[i-1][j];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Val[i][j]=Val[i][j]+Val[i][j-1];

	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			if ((i>=K)&&(j>=K)){
				F[0][i][j]=Get(i-K+1,j-K+1,i,j);
				F[1][i][j]=Get(i-K+1,j-K+1,i,j)+max(G[0][i-K][m],G[0][i][j-K]);
				F[2][i][j]=Get(i-K+1,j-K+1,i,j)+max(G[1][i-K][m],G[1][i][j-K]);
			}
			G[0][i][j]=max(F[0][i][j],max(G[0][i-1][j],G[0][i][j-1]));
			G[1][i][j]=max(F[1][i][j],max(G[1][i-1][j],G[1][i][j-1]));
			G[2][i][j]=max(F[2][i][j],max(G[2][i-1][j],G[2][i][j-1]));
		}

	printf("%d\n",max(G[2][n][m],max(G[0][n][m],G[1][n][m])));

	return 0;
}

int Get(int x1,int y1,int x2,int y2){
	return Val[x2][y2]-Val[x2][y1-1]-Val[x1-1][y2]+Val[x1-1][y1-1];
}
/*
9 9 2
1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 1 1 1 8 8 8 1 1 
1 1 1 1 1 1 8 8 8 
1 1 1 1 1 1 9 9 9 
1 1 1 1 1 1 9 9 9
//*/
