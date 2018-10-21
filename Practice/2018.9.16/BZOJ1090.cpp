#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n;
char str[maxN];
int F[maxN][maxN],Next[maxN];

int count(int x);

int main(){
	scanf("%s",str+1);n=strlen(str+1);
	for (int l=n;l>=1;l--){
		Next[l-1]=Next[l]=l-1;
		for (int i=l+1,j=l-1;i<=n;i++){
			while ((j!=l-1)&&(str[j+1]!=str[i])) j=Next[j];
			if (str[j+1]==str[i]) j++;
			Next[i]=j;
		}
		//cout<<l<<":";for (int i=l;i<=n;i++) cout<<Next[i]<<" ";cout<<endl;

		for (int r=l;r<=n;r++){
			F[l][r]=r-l+1;
			for (int k=l;k<r;k++) F[l][r]=min(F[l][r],F[l][k]+F[k+1][r]);
			for (int now=Next[r];now!=l-1;now=Next[now]){
				if ((r-l+1)%(r-now)==0) F[l][r]=min(F[l][r],F[l][l+(r-now)-1]+2+count((r-l+1)/(r-now)));
			}
		}
	}
	printf("%d\n",F[1][n]);
	return 0;
}

int count(int x){
	int ret=0;
	while (x){
		x/=10;ret++;
	}
	return ret;
}
