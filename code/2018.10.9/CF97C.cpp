#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "blasphemy"
#define RG register
#define IL inline

const int maxN=210;
const int inf=2147483647;

int n;
ld P[maxN],F[maxN][maxN*maxN];

IL ld Max(RG ld a,RG ld b);

int main(){
	//freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	scanf("%d",&n);
	RG int i,j,k;
	int up=min(n+n,200);
	for (i=0;i<=up;++i) for (j=0;j<=up*up;++j) F[i][j]=-inf;
	F[0][0]=0;
	for (i=0;i<=n;i++) cin>>P[i];//scanf("%LF",&P[i]);

	for (i=1;i<=up;++i)
		for (j=0;j<=i*n;++j)
			for (k=0;k<=n;++k)
				if (j-k+(n-k)>=0) F[i][j]=Max(F[i][j],F[i-1][j-k+(n-k)]+P[k]);
	//*/
	/*
	for (int i=1;i<=n+n;i++)
		for (int j=0;j<=i*n;j++)
			for (int k=0;k<=n;k++)
				if (j+k-(n-k)>=0) F[i][j]=max(F[i][j],F[i-1][j+k-(n-k)]+P[k]);
	//*/
	/*
	for (int i=1;i<=n+n;i++){
		for (int j=0;j<=i*n;j++)
			cout<<F[i][j]<<" ";
		cout<<endl;
	}
	//*/
	ld mx=0;
	for (i=1;i<=up;i++) mx=max(mx,F[i][0]/i);
	printf("%.10lf\n",mx);return 0;
}

IL ld Max(RG ld a,RG ld b){
	return (a>b)?(a):(b);
}
