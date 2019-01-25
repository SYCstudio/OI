#include<bits/stdc++.h>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;

int root,n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxN],NW[maxN];

void Add_Edge(int u,int v);
void dfs(int u);

int main(){
	freopen("in","r",stdin);freopen("bout","w",stdout);
	scanf("%d%d",&n,&m);mem(Head,-1);
	for (int i=1;i<=n;i++) scanf("%d",&NW[i]);
	for (int i=1;i<=n;i++){
		int a,b;scanf("%d%d",&a,&b);
		if (a==0){
			root=b;continue;
		}
		Add_Edge(a,b);Add_Edge(b,a);
	}
	dfs(root);
	while (m--){
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if (opt==1) while (a) NW[a]+=b,a=Fa[a];
		else{
			int sum=0;for (int i=a;i<=b;i++) sum+=NW[i];
			printf("%d\n",sum);
		}
	}
	return 0;
}
void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
void dfs(int u){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Fa[u])
			Fa[V[i]]=u,dfs(V[i]),NW[u]+=NW[V[i]];
	return;
}
