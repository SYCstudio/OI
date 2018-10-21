#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=11;
const int maxM=1<<maxN;
const int inf=1000000000;

int n;
int Two[maxN],O[maxM],C[maxM];
int Cost[maxM][maxM],F[maxM][maxM];
int St[maxM];

void Solve(int now,int depth);

int main(){
	Two[0]=1;for (int i=1;i<maxN;i++) Two[i]=Two[i-1]<<1;
	scanf("%d",&n);
	for (int i=1;i<=Two[n];i++) scanf("%d",&O[Two[n]-1+i]);
	for (int i=1;i<=Two[n];i++) scanf("%d",&C[Two[n]-1+i]);
	for (int i=1;i<=Two[n];i++)
		for (int j=i+1;j<=Two[n];j++){
			int key;scanf("%d",&key);
			int x=i+Two[n]-1,y=j+Two[n]-1,xx=x,yy=y;
			while (xx!=yy) xx>>=1,yy>>=1;
			//cout<<i<<" "<<j<<" "<<xx<<endl;
			Cost[xx][x]+=key;Cost[yy][y]+=key;
		}

	/*
	for (int i=1;i<=Two[n];i++)
		for (int j=Two[n];j<=Two[n+1]-1;j++)
			cout<<"("<<i<<","<<j<<") "<<Cost[i][j]<<endl;
	//*/

	Solve(1,n);

	int Ans=inf;
	for (int i=0;i<=Two[n];i++) Ans=min(Ans,F[1][i]);

	printf("%d\n",Ans);return 0;
}

void Solve(int now,int depth){
	if (depth==0){
		F[now][O[now]^1]=0;F[now][O[now]]=C[now];
		for (int i=now>>1;i!=0;i>>=1) F[now][St[i]]+=Cost[i][now];
	}
	else{
		for (int i=0;i<=Two[n];i++) F[now][i]=inf;
		St[now]=0;Solve(lson,depth-1);Solve(rson,depth-1);
		for (int i=0;i<=Two[depth-1];i++)
			for (int j=0;j<=Two[depth-1];j++)
				if (i+j>=Two[depth-1]) F[now][i+j]=min(F[now][i+j],F[lson][i]+F[rson][j]);
		St[now]=1;Solve(lson,depth-1);Solve(rson,depth-1);
		for (int i=0;i<=Two[depth-1];i++)
			for (int j=0;j<=Two[depth-1];j++)
				if (i+j<Two[depth-1]) F[now][i+j]=min(F[now][i+j],F[lson][i]+F[rson][j]);
	}
	//cout<<"Solve:"<<now<<endl;
	//for (int i=now>>1;i!=0;i>>=1) cout<<St[i];cout<<endl;
	//for (int i=0;i<=Two[depth];i++) cout<<F[now][i]<<" ";cout<<endl;
	return;
}
