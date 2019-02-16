#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=19650827;
const int inf=2147483647;

int n;
int H[maxN],F[maxN][maxN][2];

void Plus(int &x,int y);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&H[i]);
	for (int i=1;i<=n;i++) F[i][i][0]=1;
	for (int len=2;len<=n;len++)
		for (int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			if (H[l]<H[r]) Plus(F[l][r][0],F[l+1][r][1]);
			if (H[l]<H[l+1]) Plus(F[l][r][0],F[l+1][r][0]);
			if (H[r]>H[l]) Plus(F[l][r][1],F[l][r-1][0]);
			if (H[r]>H[r-1]) Plus(F[l][r][1],F[l][r-1][1]);
		}

	printf("%d\n",(F[1][n][0]+F[1][n][1])%Mod);

	return 0;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
