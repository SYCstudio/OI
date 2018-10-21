#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1510;
const int inf=2147473647;

int n,m,K;
int Val[maxN][maxN];
int A[maxN][maxN],B[maxN][maxN],C[maxN][maxN],D[maxN][maxN];

int Get(int x1,int y1,int x2,int y2);

int main(){
	//freopen("1.in","r",stdin);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Val[i][j]);

	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Val[i][j]+=Val[i][j-1];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Val[i][j]+=Val[i-1][j];
	
	for (int i=K;i<=n;i++) for (int j=K;j<=m;j++) A[i][j]=max(Get(i-K+1,j-K+1,i,j),max(A[i-1][j],A[i][j-1]));
	for (int i=K;i<=n;i++) for (int j=m-K+1;j>=1;j--) B[i][j]=max(Get(i-K+1,j,i,j+K-1),max(B[i-1][j],B[i][j+1]));
	for (int i=n-K+1;i>=K;i--) for (int j=K;j<=m;j++) C[i][j]=max(Get(i,j-K+1,i+K-1,j),max(C[i+1][j],C[i][j-1]));
	for (int i=n-K+1;i>=1;i--) for (int j=m-K+1;j>=1;j--) D[i][j]=max(Get(i,j,i+K-1,j+K-1),max(D[i+1][j],D[i][j+1]));

	int Ans=0;
	for (int i=K+1;i+K-1<=n;i++) for (int j=K;j+K<=m;j++) Ans=max(Ans,A[i-1][m]+C[i][j]+D[i][j+1]);
	for (int i=K;i+K<=n;i++) for (int j=K+1;j+K-1<=m;j++) Ans=max(Ans,A[n][j-1]+B[i][j]+D[i+1][j]);
	for (int i=K;i+K<=n;i++) for (int j=K;j+K<=m;j++) Ans=max(Ans,A[i][j]+B[i][j+1]+C[i+1][m]);
	for (int i=K;i+K<=n;i++) for (int j=K;j+K<=m;j++) Ans=max(Ans,A[i][j]+C[i+1][j]+D[1][j+1]);

	for (int i=K+K;i+K<=n;i++) for (int j=K;j<=m;j++) Ans=max(Ans,Get(i-K+1,j-K+1,i,j)+A[i-K][m]+C[i+1][m]);
	for (int i=K;i<=n;i++) for (int j=K+K;j+K<=m;j++) Ans=max(Ans,Get(i-K+1,j-K+1,i,j)+A[n][j-K]+B[n][j+1]);

	printf("%d\n",Ans);

	return 0;
}

int Get(int x1,int y1,int x2,int y2){
	return Val[x2][y2]-Val[x1-1][y2]-Val[x2][y1-1]+Val[x1-1][y1-1];
}
