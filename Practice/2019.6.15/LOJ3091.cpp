#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=110;
const int maxM=20200;

int n,m,S;
vector<int> Ser[maxN];
int F[maxN][maxM],Num[maxN];

int main()
{
	scanf("%d%d%d",&S,&n,&m);
	for (int i=1; i<=S; i++)
		for (int j=1; j<=n; j++) {
			int k;
			scanf("%d",&k);
			Ser[j].pb(k);
		}
	F[0][0]=0;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<=m; j++) F[i][j]=F[i-1][j];
		int num=0;
		for (int j=0; j<Ser[i].size(); j++) Num[++num]=Ser[i][j]*2+1;
		sort(&Num[1],&Num[num+1]);
		for (int j=1; j<=num; j++)
			for (int l=Num[j]; l<=m; l++) F[i][l]=max(F[i][l],F[i-1][l-Num[j]]+j*i);
		//for (int j=0;j<=m;j++) cout<<F[i][j]<<" ";cout<<endl;
	}
	int Ans=0;
	for (int i=0; i<=m; i++) Ans=max(Ans,F[n][i]);
	printf("%d\n",Ans);
	return 0;
}
