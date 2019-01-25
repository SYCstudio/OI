#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Block=330;
const int maxM=maxN<<1;

int n,m,root,B,Bc;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],lst[maxN],L[maxN],R[maxN];
ull NW[maxN],BAns[maxN],BLal[maxN],Sum[maxN];
int Bl[maxN],To[maxN][Block];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main(){
	scanf("%d%d",&n,&m);B=sqrt(n);Bc=(n+B-1)/B;
	for (int i=1;i<=n;i++) scanf("%llu",&NW[i]);
	for (int i=1;i<=n;i++){
		Bl[i]=i/B+1;R[Bl[i]]=r;
		if (L[Bl[i]]==0) L[Bl[i]]=i;
	}
	for (int i=1;i<=n;i++){
		int a,b;scanf("%d%d",&a,&b);
		if (a==0){
			root=b;continue;
		}
		Add_Edge(a,b);Add_Edge(b,a);
	}
	dfs(root,0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=Bc;j++)
			BAns[j]+=NW[i]*To[i][j];
	while (m--){
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if (opt==1){
			b-=NW[a];
			for (int i=1;i<=Bc;i++) BAns[i]+=b*To[a][i];
			for (int i=dfn[a];i<=R[dfn[a]];i++) 
		}
	}
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
void dfs(int u,int fa){
	++To[u][Bl[u]];dfn[u]=++dfncnt;Sum[dfn[u]]=NW[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			for (int j=1;j<=B;j++) To[V[i]][j]=To[u][j];
			dfs(V[i],u);Sum[dfn[u]]+=Sum[dfn[V[i]]];
		}
	lst[u]=dfncnt;BSum[Bl[dfn[u]]]+=Sum[dfn[u]];
	return;
}
