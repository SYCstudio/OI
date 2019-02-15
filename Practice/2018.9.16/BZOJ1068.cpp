#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=55;
const int inf=2147483647;

int n;
char str[maxN];
int F[2][maxN][maxN];

bool check(int l,int r);

int main(){
	scanf("%s",str+1);n=strlen(str+1);
	for (int len=1;len<=n;len++)
		for (int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			if (len==1){
				F[0][l][r]=1;F[1][l][r]=n+n;
				continue;
			}
			F[0][l][r]=F[1][l][r]=r-l+1;
			for (int k=l;k<r;k++) F[0][l][r]=min(F[0][l][r],F[0][l][k]+(r-k));
			for (int k=l;k<r;k++) F[1][l][r]=min(F[1][l][r],min(F[0][l][k],F[1][l][k])+1+min(F[0][k+1][r],F[1][k+1][r]));
			if ( ((r-l+1)%2==0) && (check(l,r)) ) F[0][l][r]=min(F[0][l][r],F[0][l][(l+r)/2]+1);
		}

	printf("%d\n",min(F[0][1][n],F[1][1][n]));

	return 0;
}

bool check(int l,int r){
	int mid=((l+r)>>1)+1;
	for (int i=1;l+i-1<mid;i++)
		if (str[l+i-1]!=str[mid+i-1]) return 0;
	return 1;
}
