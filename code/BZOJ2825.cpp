#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int inf=100000000;

int n,m,T;
int X[maxN],Y[maxN],V[maxN];
int F[maxN][maxN];

int Dis(int u,int v);

int main(){
	scanf("%d%d%d",&n,&m,&T);
	for (int i=1;i<=m;i++) scanf("%d%d%d",&X[i],&Y[i],&V[i]);
	for (int i=0;i<=m;i++) for (int j=0;j<=T;j++) F[i][j]=-inf;
	F[0][0]=0;
	int Ans=0;
	for (int i=0;i<m;i++)
		for (int j=0;j<=T;j++)
			if (F[i][j]!=-inf){
				for (int k=i+1;k<=m;k++)
					if (j+Dis(i,k)<=T)
						F[k][j+Dis(i,k)]=max(F[k][j+Dis(i,k)],F[i][j]+V[k]);
			}
	for (int i=1;i<=m;i++) for (int j=0;j<=T;j++) Ans=max(Ans,F[i][j]);
	printf("%d\n",Ans);return 0;
}

int Dis(int u,int v){
	return abs(X[u]-X[v])+abs(Y[u]-Y[v]);
}
