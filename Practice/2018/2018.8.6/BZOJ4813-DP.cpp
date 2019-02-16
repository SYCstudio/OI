#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int F[maxN][maxN],G[maxN][maxN],H[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);u++;v++;
		Add_Edge(u,v);Add_Edge(v,u);
	}

	dfs(1,1);

	/*
	for (int i=1;i<=n;i++){
		for (int j=0;j<=m;j++) cout<<F[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++){
		for (int j=0;j<=m;j++) cout<<G[i][j]<<" ";
		cout<<endl;
	}
	//*/

	int Ans=0;
	for (int i=0;i<=m;i++) Ans=max(Ans,max(F[1][i],G[1][i]));
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa){
	F[u][0]=G[u][0]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];
			dfs(v,u);
			for (int j=0;j<=m;j++) H[j]=F[u][j];
			for (int j=0;j<=m;j++)
				for (int k=0;k<=j;k++){
					if (j-k-1>=0) F[u][j]=max(F[u][j],G[u][k]+F[v][j-k-1]);
					if (j-k-2>=0) F[u][j]=max(F[u][j],H[k]+G[v][j-k-2]);
				}
			for (int j=0;j<=m;j++) H[j]=G[u][j];
			for (int j=0;j<=m;j++)
				for (int k=0;k<=j;k++)
					if (j-k-2>=0) G[u][j]=max(G[u][j],H[k]+G[v][j-k-2]);
		}
	return;
}
