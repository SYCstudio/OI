#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1010;

int n,Q,Seq[maxN];
double F[maxN][maxN],G[maxN][maxN];

int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) scanf("%d",&Seq[i]);
	for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) F[i][j]=Seq[i]<Seq[j];
	for (int qi=1; qi<=Q; qi++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==y) continue;
		for (int i=1; i<=n; i++) if (i!=y&&i!=x) {
				G[i][x]+=F[i][x]*0.5;
				G[i][y]+=F[i][x]*0.5;
				G[x][i]+=F[x][i]*0.5;
				G[y][i]+=F[x][i]*0.5;
			}
		for (int i=1; i<=n; i++) if (i!=x&&i!=y) {
				G[i][y]+=F[i][y]*0.5;
				G[i][x]+=F[i][y]*0.5;
				G[y][i]+=F[y][i]*0.5;
				G[x][i]+=F[y][i]*0.5;
			}
		G[y][x]=G[x][y]=(F[x][y]+F[y][x])*0.5;
		for (int i=1; i<=n; i++) F[x][i]=G[x][i],F[i][x]=G[i][x],F[y][i]=G[y][i],F[i][y]=G[i][y];
		for (int i=1; i<=n; i++) G[x][i]=G[i][x]=G[y][i]=G[i][y]=0;
		//cout<<"after "<<qi<<endl;
		//Outp();
	}
	double Ans=0;
	for (int i=1; i<=n; i++) for (int j=1; j<i; j++) Ans+=F[i][j];
	printf("%.10lf\n",Ans);
	return 0;
}