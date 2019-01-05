#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxK=20;
const int Mod=998244353;

int n,K,m;
int A[maxN];
int F[2][maxN][maxK];

void Plus(int &x,int y);
int QPow(int x,int cnt);

int main(){
	scanf("%d%d%d",&n,&K,&m);K=n-K+1;
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	int now=0;
	for (int i=1;i<=K;i++) F[now][0][i]=Mod-1;
	for (int i=1;i<=n;i++){
		now^=1;
		for (int j=0;j<=m;j++){
			F[now][j][1]=F[now^1][j][1];
			if (j>=A[i]) Plus(F[now][j][1],Mod-F[now^1][j-A[i]][1]);
			for (int k=2;k<=K;k++){
				F[now][j][k]=F[now^1][j][k];
				if (j>=A[i]) Plus(F[now][j][k],F[now^1][j-A[i]][k-1])
								 ,Plus(F[now][j][k],Mod-F[now^1][j-A[i]][k]);
			}
		}
	}
	int Ans=0;
	//for (int i=1;i<=m;i++) cout<<F[now][i][K]<<"["<<1ll*F[now][i][K]*QPow(i,Mod-2)%Mod*m%Mod<<"] ";cout<<endl;
	for (int i=1;i<=m;i++) Plus(Ans,1ll*F[now][i][K]*QPow(i,Mod-2)%Mod*m%Mod);
	printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
	x+=y;if (x>=Mod) x-=Mod;return;
}
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
