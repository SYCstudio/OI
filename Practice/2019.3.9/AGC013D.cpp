#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=3010;
const int Mod=1e9+7;

int n,m;
int F[maxN][maxN][2];

void Plus(int &x,int y);
int main()
{
	scanf("%d%d",&n,&m);
	F[0][0][1]=1;
	for (int i=1; i<=n; i++) F[0][i][0]=1;
	for (int i=0; i<m; i++) for (int j=0; j<=n; j++) for (int k=0; k<=1; k++) {
				if (!F[i][j][k]) continue;
				if (j>=1) Plus(F[i+1][j-1][k|(j==1)],F[i][j][k]),Plus(F[i+1][j][k|(j==1)],F[i][j][k]);
				if (j<n) Plus(F[i+1][j][k],F[i][j][k]),Plus(F[i+1][j+1][k],F[i][j][k]);
			}
	int Ans=0;
	for (int i=0; i<=n; i++) Plus(Ans,F[m][i][1]);
	printf("%d\n",Ans);
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}