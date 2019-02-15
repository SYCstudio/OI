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

int n,m,mxd;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];

void Add_Edge(int u,int v);
void dfs(int u,int fa,int depth);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);u++;v++;
		Add_Edge(u,v);Add_Edge(v,u);
	}

	dfs(1,1,1);

	if (mxd-1>=m) printf("%d\n",m+1);
	else printf("%d\n",min(n,mxd+(m-(mxd-1))/2));

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa,int depth){
	mxd=max(mxd,depth);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) dfs(V[i],u,depth+1);
	return;
}
