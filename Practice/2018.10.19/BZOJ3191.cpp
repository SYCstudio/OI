#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=55;
const int inf=2147483647;

int n,m;
int C[maxN];
ld F[maxN][maxN];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d",&C[i]);
	F[1][1]=1;
	for (int i=1;i<n;i++)
		for (int j=1;j<=i;j++)
			if (F[i][j])
				for (int k=1;k<=m;k++){
					int d=C[k]%(i+1);
					d=(d+j-1)%(i+1)+1;
					//cout<<i<<","<<j<<","<<k<<"->"<<d<<endl;
					F[i+1][d]+=F[i][j]/(ld)m;
				}
	for (int i=1;i<=n;i++){
		printf("%.2LF%%",F[n][i]*100);
		if (i!=n) printf(" ");
	}
	return 0;
}
