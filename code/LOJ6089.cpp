#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxSN=320;
const int Mod=23333333;
const int inf=2147483647;

int n,m;
int F[maxSN][maxSN],SF[maxSN][maxSN];

int main(){
	scanf("%d",&n);m=sqrt(n);cout<<"m:"<<m<<endl;
	F[0][0]=SF[0][0]=0;for (int i=1;i<=n;i++) SF[0][i]=1;
	for (int i=1;i<=m;i++){
		F[i][0]=SF[i][0]=0;
		for (int j=1;j<=n;j++){
			cout<<"("<<i<<","<<j<<") <- ("<<i-1<<","<<max(0,j-i*(i+1))<<")"<<endl;
			if (j-i*(i+1)<0) F[i][j]=SF[i-1][j];
			else F[i][j]=(SF[i-1][j]-SF[i-1][max(0,j-i*(i+1))]+Mod)%Mod;
			if (j-(i+1)<0) SF[i][j]=F[i][j];
			else SF[i][j]=SF[i][j-(i+1)]+F[i][j];
		}
	}
	for (int i=0;i<=m;i++){
		for (int j=1;j<=n;j++) cout<<F[i][j]<<" ";cout<<endl;
		for (int j=1;j<=n;j++) cout<<SF[i][j]<<" ";cout<<endl<<endl;
	}
}
