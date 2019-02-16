#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=110;
const int inf=2147483647;

int n,m;
int Num[maxN],INum[maxN];
ld F[maxN][maxM];
ld C[maxN][10];

ld GetC(int n,int m);

int main(){
	C[0][0]=1;
	for (int i=1;i<maxN;i++){
		C[i][0]=1;
		for (int j=1;j<=min(i,9);j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Num[i]),F[i][INum[i]=Num[i]]=1;
	ld Ans=0;
	for (int i=1;i<=n;i++) Ans+=F[i][0];
	int Q;scanf("%d",&Q);
	while (Q--){
		int u,v,key;scanf("%d%d%d",&u,&v,&key);
		Ans-=F[u][0];//Ans-=F[v][0];
		for (int j=0;j<=min(INum[u],Num[u]);j++){
			ld nf=F[u][j];F[u][j]=0;
			for (int k=0;k<=min(j,key);k++)
				F[u][j-k]+=nf/C[Num[u]][key]*C[j][k]*C[Num[u]-j][key-k];
		}

		Num[u]-=key;Num[v]+=key;
		Ans+=F[u][0];//Ans+=F[v][0];

		printf("%.11lf\n",Ans);
	}

	return 0;
}

/*
1
5
20
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
//*/
