#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dph[maxN];
map<int,int> Eg[maxN];

void Plus(int u,int v,int id);
void Add_Edge(int u,int v);
void dfs(int u,int fa,int d);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n-2;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Plus(u,v,i);Plus(u,w,i);Plus(v,w,i);
	}
	dfs(1,1,1);
	int mx=1;
	for (int i=1;i<=n;i++) if (Dph[i]>Dph[mx]) mx=i;
	dfs(mx,mx,1);
	for (int i=1;i<=n;i++) if (Dph[i]>Dph[mx]) mx=i;
	printf("%d\n",Dph[mx]);return 0;
}

void Plus(int u,int v,int id){
	if (u>v) swap(u,v);
	if ((u+1==v)||((u==1)&&(v==n))) return;
	if (Eg[u][v]==0) Eg[u][v]=id;
	else Add_Edge(id,Eg[u][v]);
	return;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs(int u,int fa,int d){
	Dph[u]=d;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) dfs(V[i],u,d+1);
	return;
}
