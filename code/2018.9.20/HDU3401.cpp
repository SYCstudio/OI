#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020;
const int inf=1000000000;

int n,mxP,W;
int F[maxN][maxN];
int Q[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d%d",&n,&mxP,&W);
		for (int i=0;i<=n;i++) for (int j=0;j<=mxP;j++) F[i][j]=-inf;
		F[0][0]=0;
		for (int i=1;i<=n;i++){
			int as,bs,ap,bp;scanf("%d%d%d%d",&ap,&bp,&as,&bs);
			int lst=max(0,i-W-1);
			for (int j=0;j<=mxP;j++) F[i][j]=max(F[i][j],F[i-1][j]);
			int L=1,R=0;
			for (int j=0;j<=mxP;j++){
				while ((L<=R)&&(Q[L]<j-as)) L++;
				if (L<=R) F[i][j]=max(F[i][j],F[lst][Q[L]]+ap*Q[L]-ap*j);
				while ((L<=R)&&(F[lst][Q[R]]+ap*Q[R]<=F[lst][j]+ap*j)) R--;
				Q[++R]=j;
			}
			L=1;R=0;
			for (int j=mxP;j>=0;j--){
				while ((L<=R)&&(Q[L]>j+bs)) L++;
				if (L<=R) F[i][j]=max(F[i][j],F[lst][Q[L]]+bp*Q[L]-bp*j);
				while ((L<=R)&&(F[lst][Q[R]]+bp*Q[R]<=F[lst][j]+bp*j)) R--;
				Q[++R]=j;
			}
		}

		/*
		for (int i=1;i<=n;i++){
			for (int j=0;j<=mxP;j++)
				cout<<F[i][j]<<" ";
			cout<<endl;
		}
		//*/

		int Ans=0;
		for (int i=0;i<=mxP;i++) Ans=max(Ans,F[n][i]);
		printf("%d\n",Ans);
	}
	return 0;
}
