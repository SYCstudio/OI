#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2000100;
const int maxM=maxN;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int F[maxN],G[maxN];
int Sorter[maxN];

void Add_Edge(int u,int v);
void dfs(int u);
bool cmp(int A,int B);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&G[i]);
	for (int i=1;i<=n;i++){
		int cnt;scanf("%d",&cnt);
		while (cnt--){
			int u;scanf("%d",&u);u++;
			Add_Edge(i,u);G[i]++;
		}
	}

	dfs(1);

	printf("%d\n",F[1]);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u){
	for (int i=Head[u];i!=-1;i=Next[i]) dfs(V[i]),F[u]+=F[V[i]];
	int scnt=0;
	for (int i=Head[u];i!=-1;i=Next[i]) Sorter[++scnt]=V[i];

	if (scnt!=0){
		sort(&Sorter[1],&Sorter[scnt+1],cmp);
		for (int i=1;i<=scnt;i++)
			if (G[u]+G[Sorter[i]]-1<=m) F[u]++,G[u]=G[u]+G[Sorter[i]]-1;
			else break;
	}

	return;
}

bool cmp(int A,int B){
	return G[A]<G[B];
}
