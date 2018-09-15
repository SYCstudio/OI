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
int Next[maxN];
int F[maxN][maxN];

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for (int i=1;i<=n;i++) F[i][i]=1;

	for (int l=n;l>=1;l--){
		Next[l]=Next[l-1]=l-1;
		for (int i=l+1,j=Next[l];i<=n;i++){
			while ((j!=l-1)&&(str[j+1]!=str[i])) j=Next[j];
			if (str[j+1]==str[i]) j++;
			Next[i]=j;
		}
		
		for (int r=l;r<=n;r++){
			F[l][r]=r-l+1;
			for (int p=l;p<r;p++)
				F[l][r]=min(F[l][r],F[l][p]+F[p+1][r]);
			for (int now=r;now!=l-1;now=Next[now])
				if ((r-l+1)%(now-Next[now])==0){
					int len=now-Next[now],cnt=min(len,F[l][l+len-1]),tot=(r-l+1)/len;
					
				}
		}
	}
}
