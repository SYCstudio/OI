#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<iostream>
using namespace std;

const int maxN=41;
const int maxM=maxN*maxN;

int n,m;
int Id[maxN][maxN],idcnt;
bitset<maxM> B[maxM];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) Id[i][j]=++idcnt;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++) {
			B[Id[i][j]][Id[i][j]]=1;
			if (i!=1) B[Id[i][j]][Id[i-1][j]]=1;
			if (i!=n) B[Id[i][j]][Id[i+1][j]]=1;
			if (j!=1) B[Id[i][j]][Id[i][j-1]]=1;
			if (j!=m) B[Id[i][j]][Id[i][j+1]]=1;
		}
	/*
	for (int i=1;i<=idcnt;i++){
		for (int j=1;j<=idcnt+1;j++) cout<<B[i][j]<<" ";cout<<endl;
	}cout<<endl;
	//*/
	for (int i=1; i<=idcnt; i++) {
		if (!B[i][i])
			for (int j=i+1; j<=idcnt; j++)
				if (B[j][i]) {
					swap(B[i],B[j]);
					break;
				}
		if (!B[i][i]) B[i][i]=1,B[i][idcnt+1]=1;
		for (int j=1; j<=idcnt; j++)
			if (i!=j&&B[j][i]) B[j]^=B[i];
	}
	/*
	for (int i=1;i<=idcnt;i++){
		for (int j=1;j<=idcnt+1;j++) cout<<B[i][j]<<" ";cout<<endl;
	}
	//*/
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++)
			printf("%d ",(int)B[Id[i][j]][idcnt+1]);
		printf("\n");
	}
	return 0;
}
