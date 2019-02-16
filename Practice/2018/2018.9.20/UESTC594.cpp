#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxH=110;
const int inf=1000000000;

int n,C;
int X[maxN];
int F[2][maxH];

int main(){
	while (scanf("%d%d",&n,&C)!=EOF){
		for (int i=1;i<=n;i++) scanf("%d",&X[i]);
		for (int i=1;i<=100;i++) F[1][i]=inf;
		for (int i=X[1];i<=100;i++) F[1][i]=(i-X[1])*(i-X[1]);
		for (int i=2;i<=n;i++){
			int now=i&1;
			for (int j=1;j<=100;j++) F[now][j]=inf;
			int mn=inf;
			for (int j=100;j>=X[i];j--){
				int key=F[now^1][j]+C*j;
				mn=min(key,mn);
				F[now][j]=min(F[now][j],mn+(j-X[i])*(j-X[i])-C*j);
			}
			mn=inf;
			for (int j=1;j<=100;j++){
				int key=F[now^1][j]-C*j;
				mn=min(key,mn);
				if (j>=X[i]) F[now][j]=min(F[now][j],mn+(j-X[i])*(j-X[i])+C*j);
			}
		}

		int Ans=inf;
		for (int i=1;i<=n;i++) Ans=min(Ans,F[n&1][i]);

		printf("%d\n",Ans);
	}

	return 0;
}
