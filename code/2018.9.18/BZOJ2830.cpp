#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n;
ld F[maxN][maxN];

int main(){
	int Q;scanf("%d%d",&Q,&n);
	if (Q==1){
		ld Ans=0;
		for (int i=1;i<n;i++) Ans=Ans+(2.0)/(ld)(i+1);
		printf("%.6LF\n",Ans);
	}
	else{
		for (int i=1;i<=n;i++) F[i][0]=1;
		for (int i=2;i<=n;i++)
			for (int d=1;d<i;d++){
				for (int j=1;j<i;j++)
					F[i][d]+=F[j][d-1]+F[i-j][d-1]-F[j][d-1]*F[i-j][d-1];
				F[i][d]/=(ld)(i-1);
			}
		ld Ans=0;
		for (int i=1;i<n;i++) Ans+=F[n][i];
		printf("%.6LF\n",Ans);
	}

	return 0;
}
