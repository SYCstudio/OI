#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=3010;
const int Mod=1e9+7;

int n,m;
int F[maxN][maxN];

void Plus(int &x,int y);
int main(){
    scanf("%d%d",&n,&m);
    F[0][m]=1;
    for (int i=0;i<=n;i++)
	for (int j=0;j<=m;j++)
	    if (F[i][j]){
		int key=F[i][j];
		Plus(F[i+1][j],key);
		if (j>=2) Plus(F[i+1][j-2],1ll*j*(j-1)/2%Mod*key%Mod);
		if (j>=1){
		    Plus(F[i+1][j-1],4ll*j%Mod*key%Mod);
		    Plus(F[i+2][j-1],1ll*j*key%Mod*(n-i-1)%Mod);
		}
	    }
    /*
    for (int i=0;i<=n;i++){
	for (int j=0;j<=m;j++) cout<<F[i][j]<<" ";cout<<endl;
    }
    //*/
    int sum=Mod-1;for (int i=0;i<=m;i++) Plus(sum,F[n][i]);
    printf("%d\n",sum);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
