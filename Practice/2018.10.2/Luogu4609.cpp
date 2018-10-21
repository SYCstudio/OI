#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxM=210;
const int Mod=1e9+7;
const int inf=2147483647;

int St[maxN][maxM];
int C[maxN][maxM];

int main(){
	for (int i=0;i<maxN;i++)
		for (int j=C[i][0]=1;j<=min(i,maxM-1);j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	St[0][0]=1;
	for (int i=1;i<maxN;i++){
		St[i][0]=0;
		for (int j=1;j<=min(i,maxM-1);j++)
			St[i][j]=(St[i-1][j-1]+1ll*St[i-1][j]*(i-1)%Mod)%Mod;
	}
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n,A,B;scanf("%d%d%d",&n,&A,&B);
		printf("%lld\n",1ll*St[n-1][A+B-2]*C[A+B-2][A-1]%Mod);
	}
	return 0;
}
