#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int inf=2147483647;

int n;
char Input[maxN+5];
ll F[maxN][maxN][maxN][maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%s",Input+1);n=strlen(Input+1);
		mem(F,0);
		F[0][0][0][0]=1;
		for (int i=0;i<n;i++)
			for (int j=0;j<=i;j++)
				for (int k=0;k<=i;k++)
					for (int l=0;k+l<=i;l++)
						if (Input[i+1]=='S'){
							F[i+1][j+1][k+1][l]+=F[i][j][k][l];
							if (j!=0){
								if (k!=0) F[i+1][j-1][k-1][l]+=F[i][j][k][l];
								else F[i+1][j-1][k][l+1]+=F[i][j][k][l];
							}
						}
						else{
							if (k!=0) F[i+1][j+1][k-1][l]+=F[i][j][k][l];
							else F[i+1][j+1][k][l+1]+=F[i][j][k][l];
							if (j!=0) F[i+1][j-1][k+1][l]+=F[i][j][k][l];
						}
		ll Ans=0;
		for (int i=0;i<=n;i++) Ans+=F[n][i][0][i];
		printf("%lld\n",Ans);
	}
	return 0;
}
/*
3
D
SSD
SDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSDSD
//*/

