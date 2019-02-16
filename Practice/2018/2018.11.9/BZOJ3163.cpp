#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

int n;
int W[maxN],V[maxN],C[maxN];
int F[maxN][maxN],G[maxN][maxN];
pair<int,int> Q[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&W[i],&V[i],&C[i]);
	//F[0][0]=0;for (int i=1;i<=1000;i++) F[0][i]=-inf;
	for (int i=1;i<=n;i++){
		C[i]=min(C[i],1000/W[i]);
		for (int j=0;j<=1000;j++) F[i][j]=F[i-1][j];
		for (int d=0;d<W[i];d++){
			int L=1,R=0;
			for (int k=d;k<=1000;k+=W[i]){
				int key=F[i-1][k]-(k-d)/W[i]*V[i];
				while ((L<=R)&&(Q[R].second<=key)) --R;
				Q[++R]=make_pair(k,key);
				while ((L<=R)&&((k-Q[L].first)/W[i]>C[i])) ++L;
				if (L<=R) F[i][k]=max(F[i][k],Q[L].second+(k-d)/W[i]*V[i]);
			}
		}
	}
	//G[n+1][0]=0;for (int i=1;i<=1000;i++) G[n+1][i]=-inf;
	for (int i=n;i>=1;i--){
		for (int j=0;j<=1000;j++) G[i][j]=G[i+1][j];
		for (int d=0;d<W[i];d++){
			int L=1,R=0;
			for (int k=d;k<=1000;k+=W[i]){
				int key=G[i+1][k]-(k-d)/W[i]*V[i];
				while ((L<=R)&&(Q[R].second<=key)) --R;
				Q[++R]=make_pair(k,key);
				while ((L<=R)&&((k-Q[L].first)/W[i]>C[i])) ++L;
				if (L<=R) G[i][k]=max(G[i][k],Q[L].second+(k-d)/W[i]*V[i]);
			}
		}
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=0;j<=10;j++) cout<<F[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++){
		for (int j=0;j<=10;j++) cout<<G[i][j]<<" ";
		cout<<endl;
	}
	//*/
	int Q;scanf("%d",&Q);
	while (Q--){
		int id,w;scanf("%d%d",&id,&w);id++;
		int Ans=0;
		for (int i=0;i<=w;i++) Ans=max(Ans,F[id-1][i]+G[id+1][w-i]);
		printf("%d\n",Ans);
	}
	return 0;
}
